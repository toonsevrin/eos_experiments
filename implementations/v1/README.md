# CirclesUBI in EOS version 1
The first version of the implementation is the most rough one, allowing only the simplest of functionality

## Smartcontract goals

* Newaccount: Creates a new account for the respective user
* Claimcoins: Claims generated coins since the last claim to an account (ie. if you call this function 10 blocks after the previous claimcoin call, you will receive 10 coins)
* Trust: Adds another account to the trusted list of the caller, the trust will only be 'useable' when the trust is made mutual.
* Untrust: Break a trust
* Exchange: Exchange coins with one of your trusted peers.

Note that this version does not allow an exchange between Bob and Alice in the following scenario: Bob and Carol trust eachother. Carol and Alice trust eachother. Ie. exchanging currency in indirect trust is not allowed.
