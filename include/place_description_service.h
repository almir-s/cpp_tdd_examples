#ifndef PLACE_DESCRIPTION_SERVICE_H
#define PLACE_DESCRIPTION_SERVICE_H
#include <memory>
#include <string>

#include <address.h>

class Http;

class PlaceDescriptionService {
   public:
   PlaceDescriptionService();
   virtual ~PlaceDescriptionService(){}

   PlaceDescriptionService(Http* http);
   std::string summaryDescription(const std::string& latitude,
                                  const std::string& longitude) const;

   private:
   std::string createGetRequestUrl(const std::string& latitude,
                                   const std::string& longitude) const;
   std::string summaryDescription(const Address& address) const;
   std::string keyValue(const std::string& key, const std::string& value) const;
   std::string get(const std::string& requestUrl) const;
   std::string summaryDescription(const std::string& response) const;

   std::shared_ptr<Http> http_;

   protected:
   virtual std::shared_ptr<Http> httpService() const;
};
#endif
