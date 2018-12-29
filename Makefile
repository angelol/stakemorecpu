CPP_IN=stakemorecpu
PUBLIC_KEY=EOS7ss3n5jGaYSNqRdZqZreXbYhUrcgyf72w6gGqtRJSEFy5BWEA5
CONTRACT_ACCOUNT=stakemorecpu
CLEOS=cleos

build:
	 eosio-cpp -abigen $(CPP_IN).cpp -o $(CPP_IN).wasm 
	
deploy: build
	$(CLEOS) set contract $(CONTRACT_ACCOUNT) . $(CPP_IN).wasm $(CPP_IN).abi

setup:
	$(CLEOS) system newaccount --stake-net "1.0000 EOS" --stake-cpu "1.0000 EOS" --buy-ram-kbytes 8000 eosio $(CONTRACT_ACCOUNT) $(PUBLIC_KEY) $(PUBLIC_KEY)
	$(CLEOS) system newaccount --stake-net "1.0000 EOS" --stake-cpu "1.0000 EOS" --buy-ram-kbytes 8000 eosio saccountfees $(PUBLIC_KEY) $(PUBLIC_KEY)
	$(CLEOS) system newaccount --stake-net "1.0000 EOS" --stake-cpu "1.0000 EOS" --buy-ram-kbytes 8000 eosio testaccount $(PUBLIC_KEY) $(PUBLIC_KEY)
	$(CLEOS) set account permission $(CONTRACT_ACCOUNT) active '{"threshold": 1,"keys": [{"key": "$(PUBLIC_KEY)","weight": 1}],"accounts": [{"permission":{"actor":"$(CONTRACT_ACCOUNT)","permission":"eosio.code"},"weight":1}]}' owner -p $(CONTRACT_ACCOUNT)

eosiocode:
	$(CLEOS) set account permission $(CONTRACT_ACCOUNT) active '{"threshold": 1,"keys": [{"key": "$(PUBLIC_KEY)","weight": 1}],"accounts": [{"permission":{"actor":"$(CONTRACT_ACCOUNT)","permission":"eosio.code"},"weight":1}]}' owner -p $(CONTRACT_ACCOUNT)

init: setup deploy
	
test:
	$(CLEOS) transfer eosio stakemorecpu "1.0000 EOS" testaccount