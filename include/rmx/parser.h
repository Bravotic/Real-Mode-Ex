/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * parser.h -- The core RMX opcode parser
 *
 * rmx_parse_opcode(byte_t *reference, byte_t terminator) -- Parses until the
 * given termination opcode is found (this could be something like iret as an
 * example)
 * 
 ***/
#include <rmx_types.h>

extern void rmx_parse_opcode(byte_t *ref, byte_t t);

#define RMX_STOP_CODE (unsigned int)0 - 2
