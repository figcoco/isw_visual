#pragma once


#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "json/json.h"

class OceanData{
public:
    virtual Json::Value json() = 0;
};

class OceanDataArray : public OceanData{
public:
    virtual OceanData* __getitem__(int index) = 0;
    virtual int __len__() = 0;
    virtual void sort() = 0;
    
};

class PointData : public OceanData{
public:
    PointData() = default;

    PointData(int time){
        _time = time;
    }

    int get_time(){
        return _time;
    }

    virtual Json::Value json() override {
        Json::Value root;
        root["time"] = _time;
        return root;
    }

    virtual ~PointData() {};
private:
    int _time;
};

class AmpPointData : public PointData{
public:
    AmpPointData () = default;

    AmpPointData (int time, float amp) : PointData(time){
        _amp = amp;
    }

    virtual Json::Value json() override {
        Json::Value root;
        root["time"] = get_time();
        root["amp"] = _amp;
        return root;
    }

    virtual ~AmpPointData() {};
private:
    float _amp;
};


class TimeDataArray : public OceanDataArray{
public:
    TimeDataArray () = default;

    TimeDataArray (int x, int y) {
        _x = x;
        _y = y;
    }

    int get_x() {return _x;}
    int get_y() {return _y;}

    virtual void sort() override {
        // std::sort(_array.begin(), _array.end(), [](Json::Value a, Json::Value b){
        //     return a["time"] < b["time"];
        // });
        std::sort(m_array.begin(), m_array.end(), [](PointData* a, PointData* b){
            return a->get_time() < b->get_time();
        });
        _array.clear();
        for (auto i : m_array) {
            _array.append(i->json());
        }
    }

    virtual int __len__() override {
        return m_array.size();
    }

    virtual PointData* __getitem__(int index) override {
        return m_array[index];
    }

    void add(PointData* data) {
        _array.append(data->json());
        m_array.push_back(data);
    }

    virtual Json::Value json() override {
        Json::Value root;
        root["x"] = _x;
        root["y"] = _y;
        root["data"] = _array;
        return root;
    }

    virtual ~TimeDataArray() {
        for (auto i : m_array) {
            if (i != nullptr) {
                delete i;
            }
        }
    }

private:
    Json::Value _array;
    std::vector<PointData*> m_array;
    int _x;
    int _y;
};

class SpaceDataArray : public OceanDataArray{
public:
    SpaceDataArray() = default;
    
    virtual void sort() override {
        // std::sort(_array.begin(), _array.end(), [](Json::Value a, Json::Value b){
        //     return a["x"] < b["x"];
        // });
        // std::sort(_array.begin(), _array.end(), [](Json::Value a, Json::Value b){
        //     return a["y"] < b["y"];
        // });
        // for (auto i : _array) {
        //     i["data"].sort();
        // }
        std::sort(m_array.begin(), m_array.end(), [](TimeDataArray* a, TimeDataArray* b){
            return a->get_x() < b->get_x();
        });
        std::sort(m_array.begin(), m_array.end(), [](TimeDataArray* a, TimeDataArray* b){
            return a->get_y() < b->get_y();
        });
        for (auto i : m_array) {
            i->sort();
        }

        _array.clear();
        for (auto i : m_array) {
            _array.append(i->json());
        }
    }

    TimeDataArray* _get_time_data_array(int x, int y) {
        for (auto data : m_array) {
            if (data->get_x() == x && data->get_y() == y) {
                return data;
            }
        }
        TimeDataArray* time_data_array = new TimeDataArray(x, y);
        add(time_data_array);
        return time_data_array;
    }

    void add_point_data(int x, int y, PointData* data) {
        auto time_data_array = _get_time_data_array(x, y);
        time_data_array->add(data);
    }

    virtual int __len__() override {
        return m_array.size();
    }

    virtual TimeDataArray* __getitem__(int index) override {
        return m_array[index];
    }

    void add(TimeDataArray* data) {
        _array.append(data->json());
        m_array.push_back(data);
    }

    virtual Json::Value json() override {
        Json::Value root;
        root["data"] = _array;
        return root;
    }

    virtual ~SpaceDataArray() {
        for (auto dataArray : m_array) {
            if (dataArray != nullptr) {
                delete dataArray;
            }
        }
    }

private:
    Json::Value _array;
    std::vector<TimeDataArray*> m_array;
};