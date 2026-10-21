Bits.c holds the functions print_binary, get_field, set_field, and sign_extend which use masking and bit shifting to return and print various bit ranges such as pos-pos+width-1 which are then passed to test_bits.c for verification. 

To build and test the only command that needs to be run is make test and make clean if needed. 

Width accepts values from 1 to 32, pos can be from 0 to 31, and pos + width must not exceed 32. set_field value must be less than 2^width, ex. if width is 4, value is 0 to 15 because value = 2^width -1. 

If value exceeds 2^width - 1, it automatically gets masked so set_field(0x0, 0, 4, 0xFF) would only use the lowest 4 bits of 0xFF. 

Status_unpack doesn't have any special handling for when MODE is 5,6, or 7, it just returns the value and it's up to the caller to check if MODE is a valid value. 