#pragma once
#include <string>
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any

namespace bdnE
{
    class Observer
    {
    public:
        Observer() = default;
        virtual ~Observer() = default;
        Observer(const Observer&) = delete;
        Observer(Observer&&) = delete;
        Observer& operator=(const Observer&) = delete;
        Observer& operator=(Observer&&) = delete;

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) = 0;
    };
}