/*
 * File:   lrucache.hpp
 * Author: Alexander Ponomarev
 *
 * Created on June 20, 2013, 5:09 PM
 */

#ifndef _LRUCACHE_HPP_INCLUDED_
#define    _LRUCACHE_HPP_INCLUDED_

#include <unordered_map>
#include <list>
#include <vector>
#include <cstddef>
#include <stdexcept>

namespace cache {

template<typename size_t, typename value_t>
class lru_cache {
public:
    typedef typename std::pair<size_t, value_t> key_value_pair_t;
    typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;
    
    lru_cache(size_t max_size, size_t way_size):_max_size(max_size), _way_size(way_size){
            
            if(max_size<way_size)
                  throw std::range_error("Wrong size defined");
            for(size_t i = 0; i < _way_size; i++)
            {
                std::unordered_map <size_t, list_iterator_t>_cache_items_map;
                _cache_items_map_v.push_back(_cache_items_map);
            }
    }
    
    void put(const size_t& key, const value_t& value) {
        int loc = (key-1) % _way_size;
        auto it = _cache_items_map_v[loc].find(key);
        _cache_items_list.push_front(key_value_pair_t(key, value));
        if (it != _cache_items_map_v[loc].end()) {
            _cache_items_list.erase(it->second);
        }
        _cache_items_map_v[loc][key] = _cache_items_list.begin();
        
        if (_cache_items_list.size() > (unsigned long)_max_size ) {
          
            auto last = _cache_items_list.end();
            last--;
            loc = (last->first -1) % _way_size;
            _cache_items_map_v[loc].erase(last->first);
            _cache_items_list.pop_back();
        }
    }
    
    const value_t& get(const size_t& key) {
        int loc = (key-1) % _way_size;
        auto it = _cache_items_map_v[loc].find(key);
        if (it == _cache_items_map_v[loc].end()) {
            throw std::range_error("There is no such key in cache");
        } else {
            _cache_items_list.splice(_cache_items_list.begin(), _cache_items_list, it->second);
            return it->second->second;
        }
    }
    
    bool exists(const size_t& key) const {
        int loc = (key-1) % _way_size;
        return _cache_items_map_v[loc].find(key) != _cache_items_map_v[loc].end();
    }
    
    size_t size() const {
        size_t sum_size = 0;
        for(size_t i = 0; i < _way_size; i++)
            sum_size += _cache_items_map_v[i].size();
        return sum_size;
    }
    
private:
    std::list<key_value_pair_t> _cache_items_list;
    std::vector<std::unordered_map <size_t, list_iterator_t>>_cache_items_map_v;
    size_t _max_size;
    size_t _way_size;
};

} // namespace cache

#endif    /* _LRUCACHE_HPP_INCLUDED_ */

