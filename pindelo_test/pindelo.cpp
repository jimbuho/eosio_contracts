#include "pindelo.hpp"

/**
 * @brief Register Company
 * @param account <eosio::name> Company account name
 * @param string <string> Company bussiness name
 * @author Diego Gonzalez <github.com/jimbuho>
 */
void pindelo::signup(const name account, string name)
{
	// Validate account isn't stored
	company_table companies(_self, _self.value);
	auto iter = companies.find(account.value);

	eosio::check(iter == companies.end(), "Company already registered");

	// Create and store account
	companies.emplace(account, [&](auto &user) {
		user.account = account;
		user.name = name;
	});
}

/**
 * @brief Assign Post
 * @param account <eosio::name> Company's account name
 * @param code <eosio::uint64_t> Post code
 * @param creationDate <string> Post creatiom date
 * @param creationUser <string> Post createion user
 * @param mainPicture <string> Post main picture url
 * @param content <string> Post content text
 * @param location <string> Post geolocation string
 * @param process <process_c> Post process
 * @param data <std::vector<key_value_c>> Post extra data
 * @author Diego Gonzalez <github.com/jimbuho>
 */
void pindelo::addpost(const name account,
        const uint64_t code, 
        const string creationDate,
        const string creationUser,
        const string mainPicture,
        const string content,
        const string location,
		const std::vector<key_value_c> data,
        const process_c process)
{
	// Create and setup a new post
	post_table posts(_self, account.value);

	auto post = posts.emplace(account, [&](auto &item) {
		item.code = code;
		item.creationDate = creationDate;
		item.creationUser = creationUser;
		item.mainPicture = mainPicture;
		item.content = content;
		item.location = location;
		item.process = process;

		item.data.reserve( data.size() );
        for ( auto& extraData : data ) {
           item.data.push_back( extraData );
        }
	});
}

/**
 * @brief Post search
 * @param account <eosio::name> Company's account name
 * @param code <eosio::uint64_t> Post code
 * @author Diego Gonzalez <github.com/jimbuho>
 */
 /*
post_table pindelo::getpost(const name account, const uint64_t code)
{
	// Fetch the posts within the account company
	post_table posts(_self, account.value);

	auto itr = posts.find(code);

	eosio::check(itr != posts.end(), "Post code not founded");

	return itr;
}*/