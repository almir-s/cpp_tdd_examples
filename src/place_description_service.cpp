#include <address.h>
#include <address_extractor.h>
#include <curl_http.h>
#include <http.h>
#include <place_description_service.h>

#include <iostream>
#include <memory>
#include <string>

using namespace std;
// PlaceDescriptionService::PlaceDescriptionService(Http* http) : http_(http) {}
// PlaceDescriptionService::~PlaceDescriptionService(){};

PlaceDescriptionService::PlaceDescriptionService()
    : http_{make_shared<CurlHttp>()} {}

string PlaceDescriptionService::summaryDescription(
    const string& latitude, const string& longitude) const {
   auto request = createGetRequestUrl(latitude, longitude);
   auto response = get(request);
   AddressExtractor extractor;
   auto address = extractor.addressFrom(response);
   return address.summaryDescription();
}

string PlaceDescriptionService::summaryDescription(
    const string& response) const {
   AddressExtractor extractor;
   auto address = extractor.addressFrom(response);
   return address.summaryDescription();
}

shared_ptr<Http> PlaceDescriptionService::httpService() const { return http_; }
string PlaceDescriptionService::get(const string& requestUrl) const {
   auto http = httpService();
   http->initialize();
   auto response = http->get(requestUrl);
   return response;
}

string PlaceDescriptionService::createGetRequestUrl(
    const string& latitude, const string& longitude) const {
   string server{"http://open.mapquestapi.com/"};
   string document{"nominatim/v1/reverse"};
   return server + document + "?" + keyValue("format", "json") + "&" +
          keyValue("lat", latitude) + "&" + keyValue("lon", longitude);
}

string PlaceDescriptionService::keyValue(const string& key,
                                         const string& value) const {
   return key + "=" + value;
}
