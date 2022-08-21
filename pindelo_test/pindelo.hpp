#include <eosio/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

struct key_value_c {
  string key;
  string value;

  // explicit serialization macro is not necessary, used here only to improve compilation time
  EOSLIB_SERIALIZE( key_value_c, (key)(value) )
};

struct process_c {
  string name;
  string title;
  string processType;
  string productType;

  // explicit serialization macro is not necessary, used here only to improve compilation time
  EOSLIB_SERIALIZE( process_c, (name)(processType)(productType))
};

class[[eosio::contract]] pindelo : public contract
{
  public:
	using contract::contract;

	[[eosio::action]] void signup(const name account, const string name);

	[[eosio::action]] void addpost(
        const name account, 
        const uint64_t code, 
        const string creationDate,
        const string creationUser,
        const string mainPicture,
        const string content,
        const string location,
        const std::vector<key_value_c> data,
        const process_c process);
    
	/*[[eosio::action]] post_table getpost(
        const name account,
        const uint64_t code);*/

  private:
	struct [[eosio::table]] Company
	{
		name account;
        string name;
		auto primary_key() const { return account.value; };
	};

	struct [[eosio::table]] Post
	{
		uint64_t code;
		string creationDate;
        string creationUser;
        string mainPicture;
        string content;
        string location;
        process_c process;
        std::vector<key_value_c> data;
        
		auto primary_key() const { return code; };
	};

	typedef multi_index<"companies"_n, Company> company_table;
	typedef multi_index<"posts"_n, Post> post_table;
};