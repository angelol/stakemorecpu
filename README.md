# stakemorecpu

This is a smart contract designed to help people who are locked out of their accounts due to low CPU. In those situations, the available CPU resources do not even allow to stake more EOS toward CPU, effectively locking people out of their accounts. It's also not possible to use Chintai or BankOfStaked in this situation.

## How to use?

This contract is deployed on the EOS mainnet on the account ```stakemorecpu```. Simply transfer the amount of EOS you would like to stake to this account. In the memo, give the account to which the CPU should be staked and transferred.

You can make a withdrawal from an exchange and unlock your account by staking more CPU.

For example, if your account is ```helpimlocked```, make a withdrawal of ```10.0000 EOS``` from an exchange to ```stakemorecpu``` and specify ```helpimlocked``` as memo. It's important to give the correct memo as the transfer will be rejected otherwise.
