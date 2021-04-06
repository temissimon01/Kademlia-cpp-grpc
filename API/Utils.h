#pragma once

#include <boost/random.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <openssl/sha.h>

namespace Utils {

	static bool RANDOM_GENERATOR_CREATED = false;
	static boost::random::independent_bits_engine<boost::random::mt19937_64, 64, uint64_t> MAGIC_GENERATOR;

	static uint64_t generate_magic() {

		if (!RANDOM_GENERATOR_CREATED) {
			RANDOM_GENERATOR_CREATED = true;
			MAGIC_GENERATOR.seed(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}

		return MAGIC_GENERATOR();
	}

	static boost::multiprecision::cpp_int hash_key(std::string key, unsigned int size_bytes) {
		unsigned char hash[SHA512_DIGEST_LENGTH];

		SHA512_CTX ctx;

		SHA512_Init(&ctx);
		SHA512_Update(&ctx, key.data(), key.length());
		SHA512_Final(hash, &ctx);

		std::stringstream ss;

		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
			ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
		}

		std::string source = ss.str();
		source = source.substr(0, size_bytes / (unsigned int)4);

		boost::multiprecision::uint512_t val("0x"+ss.str());

		return val;
	}

};