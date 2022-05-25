#include <unordered_map>
#include <string>
#include <vector>

#ifndef _KVS_CORE
#define _KVS_CORE
namespace TRKVS {
class KVS {
   private:
    std::unordered_map<std::string, std::unordered_map<std::string, int>::iterator> keys;
    std::unordered_map<std::string, int> values;

   public:
    const std::vector<std::string> get_keys();
    void set_item(const std::string, const std::string);
    const std::string get_item(const std::string);
    void delete_item(const std::string);
    const int count_of(std::string);
};
}  // namespace TRKVS

#endif