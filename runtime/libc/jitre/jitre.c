void jitre_error_handler(const char* r, unsigned char d){
    printf("JITRE has paused the program\nReason: %s\nOpcode: 0x%2x", r, d);
}