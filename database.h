#pragma once

#include "date.h"

#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& ostream, const pair<Date, string>& event);
bool operator< (const pair<Date, vector<string>>& lhs, const Date& rhs);
bool operator< (const Date& lhs, const pair<Date, vector<string>>& rhs);
Date LastDate(const set<Date>& db, const Date& last);

class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& ostream) const;

    template<typename Func>
    int RemoveIf(const Func& predicate);

    template<typename Func>
    vector<pair<Date, string>> FindIf(Func predicate) const;

    pair<Date, string> Last(const Date& date) const;
private:
    map<Date, vector<string>> database;
    map<Date, set<string>> databaseSet;
    set<Date> allDates;
};



template<typename Func>
int Database::RemoveIf(const Func& predicate) {
    int count = 0;
    set<Date> removeList;
    for (auto& dateEvents : database) {
        size_t init_count = dateEvents.second.size();
        Date date = dateEvents.first;

        //чистим вектор
        dateEvents.second.erase(remove_if(dateEvents.second.begin(), dateEvents.second.end(),
                                          [date, predicate](const string& event){
            return predicate(date, event);
        }), dateEvents.second.end());

        //чистим set
        set<string> events;
        for (const auto& e : dateEvents.second) {
            events.insert(e);
        }
        databaseSet[date] = events;

        count += init_count - dateEvents.second.size();

        if(dateEvents.second.empty()) {
            removeList.insert(date);
        }
    }

    for(const auto& date : removeList) {
        database.erase(date);
        databaseSet.erase(date);
        allDates.erase(date);
    }

    return count;
}

template<typename Func>
vector<pair<Date, string>> Database::FindIf(Func predicate) const {
    vector<pair<Date, string>> foundedEvents;
    for (const auto& dateEvents : database) {
        Date date = dateEvents.first;
        for (const auto& event : dateEvents.second) {
            if(predicate(date, event)) {
                foundedEvents.push_back(make_pair(date, event));
            }
        }
    }
    return foundedEvents;
}
