#include <address_extractor.h>

#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "json/reader.h"

using namespace std;
using namespace Json;

Address AddressExtractor::addressFrom(const string& json) const {
   Address address;
   Value jsonAddress{jsonAddressFrom(json)};
   populate(address, jsonAddress);
   return address;
}

Value AddressExtractor::jsonAddressFrom(const string& json) const {
   auto location = parse(json);
   return location.get("address", Value::null);
}

void AddressExtractor::populate(Address& address, Value& jsonAddress) const {
   address.road = getString(jsonAddress, "road");
   address.city = getString(jsonAddress, "city");
   address.state = getString(jsonAddress, "state");
   address.country = getString(jsonAddress, "country");
}

Value AddressExtractor::parse(const string& json) const {
   Value root;
   CharReaderBuilder builder;
   const std::unique_ptr<CharReader> reader(builder.newCharReader());
   reader->parse(json.c_str(), json.c_str() + json.length(), &root, nullptr);
   return root;
}

string AddressExtractor::getString(Value& result, const string& name) const {
   return result.get(name, "").asString();
}
