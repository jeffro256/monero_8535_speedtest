#include <fstream>
#include <iostream>

#include "file_io_utils.h"
#include "rpc/core_rpc_server_commands_defs.h"
#include "storages/portable_storage_template_helper.h"
#include "time_helper.h"

#define NUM_ITERS 100000

int main()
{
	// This is what my stagenet daemon returned when I requested with heights = { 1111111 }
	cryptonote::COMMAND_RPC_GET_BLOCKS_BY_HEIGHT::response saved_response = AUTO_VAL_INIT(saved_response);
	std::string resp_str;
 	if (!epee::file_io_utils::load_file_to_string("gbbh_resp.bin", resp_str))
	{
		std::cerr << "coudlnt read file" << std::endl;
		return -1;
	}
	if (!epee::serialization::load_t_from_binary(saved_response, resp_str))
	{
		std::cerr << "no load from binary" << std::endl;
		return -1;
	}

	uint64_t random_data; // We'll fudge w/ random data to prevent optimizations
	std::ifstream ifs("/dev/urandom");
	ifs.read(reinterpret_cast<char*>(&random_data), sizeof(random_data));
	uint64_t optim_preventer = 0;

	std::cout << "old buffer simulation start" << std::endl;
	const uint64_t old_start = epee::misc_utils::get_tick_count();
	for (size_t i = 0; i < NUM_ITERS; i++)
	{
		std::string m_body; // reponse_info.m_body
		epee::byte_slice buffer;
		epee::serialization::store_t_to_binary(saved_response, buffer, 64 * 1024);
		m_body.assign(reinterpret_cast<const char*>(buffer.data()), buffer.size());
		optim_preventer += m_body[random_data * optim_preventer % m_body.size()];
	}
	const uint64_t old_finish = epee::misc_utils::get_tick_count();
	const uint64_t old_elapsed = old_finish - old_start;
	std::cout << "elapsed milliseconds: " << old_elapsed << std::endl;
	std::cout << "optimization prevent result: " << optim_preventer << std::endl;

	//////////////////////////////////////////////////////////////////////////////////

	std::cout << "new string simulation start" << std::endl;
        const uint64_t new_start = epee::misc_utils::get_tick_count();
        for (size_t i = 0; i < NUM_ITERS; i++)
        {
                std::string m_body; // reponse_info.m_body
                epee::serialization::store_t_to_binary(saved_response, m_body, 64 * 1024);
                optim_preventer += m_body[random_data * optim_preventer % m_body.size()];
        }
        const uint64_t new_finish = epee::misc_utils::get_tick_count();
        const uint64_t new_elapsed = new_finish - new_start;
        std::cout << "elapsed milliseconds: " << new_elapsed << std::endl;
        std::cout << "optimization prevent result: " << optim_preventer << std::endl;

	return 0;
}
