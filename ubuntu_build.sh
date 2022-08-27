g++ -std=c++14 -DAUTO_INITIALIZE_EASYLOGGINGPP -o xmr_8535_speedtest -Ofast \
    -I monero/contrib/epee/include/ -I monero/src/ -I monero/external/easylogging++/ \
    monero/contrib/epee/src/portable_storage.cpp monero/contrib/epee/src/parserse_base_utils.cpp monero/external/easylogging++/easylogging++.cc monero/contrib/epee/src/byte_stream.cpp monero/contrib/epee/src/byte_slice.cpp monero/contrib/epee/src/misc_language.cpp monero/contrib/epee/src/file_io_utils.cpp \
    main.cpp -lboost_thread -lboost_filesystem -lboost_regex -lboost_system
