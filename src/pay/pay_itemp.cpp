#include <algorithm>
#include "pay_item.h"

bool PayItem::hasTax(std::string taxName){
    return (std::find(taxes_.begin(),taxes_.end(),taxName) != taxes_.end());
}