#include "stakemorecpu.hpp"

ACTION stakemorecpu::transfer(const name from, const name to, const asset quantity, const std::string memo) {
  // only respond to incoming transfers
  if (from == _self || to != _self) {
    return;
  }
  // only handle EOS transfers, ignore anything else
  if(quantity.symbol != core_symbol) {
    return;
  }
  
  eosio_assert(quantity.is_valid(), "Are you trying to corrupt me?");
  eosio_assert(quantity.amount > 0, "Amount must be > 0");
  
  const asset fee{quantity.amount/100, core_symbol};
  const auto ram_replace_amount = buyrambytes(450);
  const asset stake_net{0, core_symbol};
  const asset stake_cpu = quantity - fee - ram_replace_amount;
  
  action(
    permission_level{ _self, "active"_n},
    system_account,
    "buyram"_n,
    make_tuple(_self, _self, ram_replace_amount)
  ).send();
  
  action(
    permission_level{ _self, "active"_n},
    eosio_token_account,
    "transfer"_n,
    std::make_tuple(_self, "saccountfees"_n, fee, std::string("Fee"))
  ).send();
  
  action(
    permission_level{ _self, "active"_n},
    system_account,
    "delegatebw"_n,
    std::make_tuple(_self, name(memo), stake_net, stake_cpu, true)
  ).send();
}

extern "C" {
  [[noreturn]] void apply(uint64_t receiver, uint64_t code, uint64_t action) {
    if (action == "transfer"_n.value && code == stakemorecpu::eosio_token_account.value) {
      execute_action(eosio::name(receiver), eosio::name(code), &stakemorecpu::transfer);
    }
    eosio_exit(0);
  }
}