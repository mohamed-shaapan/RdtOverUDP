#include "checksum_calculator.h"

checksum_calculator::checksum_calculator() {}


uint16_t  checksum_calculator::get_checksum(string chunk) {

  // divide each chunk to 16-bit pieces (two character)
  vector<string> to_sum = text_handler::divide_data_size(chunk, 2) ;

  // sum all 16-bit words
  bitset<16> checksum(0) ;
  for( string s : to_sum ) {
    bitset<8> first(s[0]);
    bitset<8> second(s[1]);
    bitset<16> str_bits (first.to_ulong() * 0x100 + second.to_ulong());
    checksum = bitset<16>(checksum.to_ulong() + str_bits.to_ulong()) ;
  }

  // obtain 1's compliment of check sum
  for (int i = 0 ; i < checksum.size() ; i++) {
    checksum[i] = checksum[i] ^ 1 ;
  }

  return checksum.to_ullong();
}


/*
 * call this function like that validate(packet.get_checksum(),packet.calc_checksum())
 * */
bool checksum_calculator::validate(uint16_t sent_checksum, uint16_t new_checksum) {

  bitset<16> sum = bitset<16>(sent_checksum + new_checksum);
  for(int i = 0 ; i < sum.size() ; i++){
    if(sum[i])
      return true;
  }
  return false;
}
