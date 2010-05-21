// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "storage.hh"
#include "log.hh"
#include <fnmatch.h>

using namespace kyotocabinet;

KVStore KVStore::instance_;

KVStore& KVStore::instance()
{
    return instance_;
}

bool KVStore::init(std::string data_dir)
{
    std::string db_name = data_dir + "kp_default.kch";
    std::string index_name = data_dir + "kp_index.xap";

    l(lg::debug, "opening hash db [%s]", db_name.c_str());

    if (not db_.open(db_name.c_str(), HashDB::OWRITER | HashDB::OCREATE))
    {
        l(lg::error, "error opening hash db [%s]: %s", db_name.c_str(), db_.error().name());
        return false;
    }

    l(lg::debug, "opening index [%s]", index_name.c_str());

    try
    {
        index_ = new Xapian::WritableDatabase(index_name.c_str(), Xapian::DB_CREATE_OR_OPEN);
    }
    catch (const Xapian::Error& error)
    {
        l(lg::error, "error opening index [%s]: %s", index_name.c_str(), error.get_msg().c_str());
        return false;
    }

    return true;
}

void KVStore::fini()
{
    if (not db_.close())
    {
        l(lg::error, "error closing hash db: %s", db_.error().name());
    }
    if (index_ != NULL)
    {
        delete index_;
    }
}

void KVStore::put(const std::string& key, const std::string& data)
{
    if (not db_.set(key, data))
    {
        l(lg::error, "error setting data for key %s: %s", key.c_str(), db_.error().name());
    }

    try
    {
        Xapian::TermGenerator indexer;
        Xapian::Document document;

        document.set_data(key); // yep, we store only the keys as xapian documents

        indexer.set_document(document);
        indexer.index_text(data);

        index_->add_document(document);
        index_->commit();
    }
    catch (const Xapian::Error& error)
    {
        l(lg::error, "error indexing key %s: %s", key.c_str(), error.get_msg().c_str());
    }
}

void KVStore::search(const std::string& pattern, std::vector<std::string>& result)
{
    try
    {
        Xapian::Enquire enquire(*index_);
        Xapian::QueryParser qp;

        qp.set_database(*index_);

        Xapian::Query query = qp.parse_query(pattern);

        l(lg::debug, "parsed query is: %s", query.get_description().c_str());

        enquire.set_query(query);

        Xapian::MSet matches = enquire.get_mset(0, index_->get_doccount());

        for (Xapian::MSetIterator msi = matches.begin(); msi != matches.end(); msi++)
        {
            result.push_back(msi.get_document().get_data());
        }
    }
    catch (const Xapian::Error& error)
    {
        l(lg::error, "error searching pattern %s: %s", pattern.c_str(), error.get_msg().c_str());
    }
}

void KVStore::keys(const std::string& pattern, std::vector<std::string>& result)
{
    class KeySearcher : public DB::Visitor
    {
    private:
        const std::string& pattern_;
        std::vector<std::string>& result_;

    public:
        KeySearcher(const std::string& pattern, std::vector<std::string>& result)
            : pattern_(pattern), result_(result)
        {
        }

        const char* visit_full(const char* kbuf, size_t ksiz, const char*, size_t, size_t *)
        {
            std::string key(kbuf, ksiz);

            if (fnmatch(pattern_.c_str(), key.c_str(), FNM_NOESCAPE) == 0)
            {
                result_.push_back(key);
            }

            return NOP;
        }

        const char* visit_empty(const char*, size_t, size_t *)
        {
            return NOP;
        }
    } searcher(pattern, result);

    if (not db_.iterate(&searcher, false))
    {
        l(lg::error, "iterate error: %s", db_.error().name());
    }
}

void KVStore::get(const std::string& key, std::string& data)
{
    // TODO: use a smart pointer
    std::string* value = db_.get(key);
    if (value)
    {
        data = *value;
        delete value;
    }
}

uint64_t KVStore::size()
{
    return db_.count();
}

bool KVStore::exists(const std::string& key)
{
    // TODO: use a smart pointer
    std::string* value = db_.get(key);
    bool found = false;
    if (value)
    {
        found = true;
        delete value;
    }

    return found;
}

void KVStore::remove(const std::string& key)
{
    db_.remove(key);
}

void KVStore::rename(const std::string& oldkey, const std::string& newkey)
{
    // TODO: make a transaction class (scoped) and use a smart_ptr
    db_.begin_transaction(true);
    std::string* value = db_.get(oldkey);
    if (value)
    {
        db_.set(newkey, *value);
        delete value;
    }
    db_.remove(oldkey);
    db_.end_transaction(true);
}
