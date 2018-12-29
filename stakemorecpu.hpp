#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include "exchange_state.hpp"

using namespace eosio;

CONTRACT stakemorecpu : public contract {
   public:
      using contract::contract;
      
      static constexpr symbol core_symbol{"EOS", 4};
      static constexpr name system_account{"eosio"};
      static constexpr name eosio_token_account{"eosio.token"};
      static constexpr symbol RAM_symbol{"RAM", 0};

      ACTION transfer(
        const name from, 
        const name to, 
        const asset quantity, 
        const std::string memo
      );
    
    private:
      asset buyrambytes(uint32_t bytes) {
        rammarket rammarkettable(system_account, system_account.value);
        auto itr = rammarkettable.find(symbol{"RAMCORE", 4}.raw());
        auto tmp = *itr;
        auto ram_price = tmp.convert(asset(bytes, RAM_symbol), core_symbol);
        ram_price.amount = (ram_price.amount * 200 + 199) / 199; // add ram fee
        return ram_price;
      }
};

