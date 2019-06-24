#include "database.h"

#include <string>
#include <utility>
#include <map>
#include <vector>
using namespace std;

void Database::Add(const Date& date, const string& event) {
    //по вектору
    /*if (database.count(date) != 0 &&
            find(database.at(date).begin(), database[date].end(), event) != database[date].end()) {
        return;
    }*/

    //по сету
    if (allDates.count(date) != 0 &&
            databaseSet.at(date).count(event) != 0) {
        return;
    }
    database[date].push_back(event);
    databaseSet[date].insert(event);
    allDates.insert(date);
}

void Database::Print(ostream& ostream) const {
    for (const auto& item : database)
        for (const string& event : item.second)
            ostream << item.first << " " << event << endl;
}

//pair<Date, string> Database::Last(const Date& date) const {
//    if(database.size() == 0 || date < database.begin()->first) {
//        throw invalid_argument("");
//    }

    /*
    auto it = find_if(database.begin(), database.end(), [date](const pair<Date, vector<string>>& dateEvents){
        return date < dateEvents.first;
    });
    it = prev(it);
    */
    /*
    auto it = upper_bound(database.begin(), database.end(), date);
    it = prev(it);
    */
    /*
    auto it = database.begin();
    for (it; it != database.end() && it->first <= date; it++);
    it = prev(it);
    */

//    Date last = LastDate(allDates, date);
//    return make_pair(last, database.at(last)[database.at(last).size() - 1]);
    //return make_pair(it->first, it->second[it->second.size() - 1]);
//}

pair<Date, string> Database::Last(const Date& date) const {
    auto it = database.upper_bound(date);

    if ((it != database.end() && it != database.begin()) || (it == database.end() && database.size() > 0)) {
        return make_pair(prev(it)->first, prev(it)->second.back());
    }
    else {
        throw invalid_argument("");
    }
}

Date LastDate(const set<Date>& allDates, const Date& last) {
    auto it = upper_bound(allDates.begin(), allDates.end(), last);
    it = prev(it);
    return *it;
}

bool operator< (const pair<Date, vector<string>>& lhs, const Date& rhs) {
    return lhs.first < rhs;
}
bool operator< (const Date& lhs, const pair<Date, vector<string>>& rhs) {
    return lhs < rhs.first;
}

ostream& operator<< (ostream& ostream, const pair<Date, string>& event) {
    ostream << event.first << " " << event.second;
    return ostream;
}
