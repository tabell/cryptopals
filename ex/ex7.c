#include <openssl/evp.h>

#include "lib/common.h"
#include "lib/file.h"

#define errn(str, err, ...) fprintf(stderr, "error %d during %s: %s\n", err, str, strerror(err))

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr,"usage: %s <encrypted file> <keyfile>\n", argv[0]);
        return 0;
    }

    uint8_t *key = NULL;
    uint8_t *ct = NULL;
    int ret;
    size_t ct_len;
    if (0 != (ret = file_read_alloc(argv[1], &ct, &ct_len))) {
        errn("loading ciphertext file", ret);
        return 0;
    } else {
        dbg("read %lu bytes from enciphered file", ct_len);
    }

    size_t key_len;
    if (0 != (ret = file_read_alloc(argv[2], &key, &key_len))) {
        errn("loading ciphertext file", ret);
        goto done;
    } else {
        dbg("read %lu bytes from keyfile", key_len);
    }

    uint8_t *out = malloc(ct_len);

    /* Crypto begin */
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        fprintf(stderr,"EVP_CIPHER_CTX_init failed\n");
        goto key_free;
    }

    if (1 != (EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))) {
        fprintf(stderr,"EVP_DecryptInit_ex failed\n");
        goto cleanup_ctx;
    }

    int out_len = 0;
    if (1 != (EVP_DecryptUpdate(ctx, out, &out_len, ct, ct_len))) {
        fprintf(stderr,"EVP_DecryptUpdate failed\n");
        goto cleanup_ctx;
    }
    if (out_len) fprintf(stderr, "update wrote %d bytes\n", out_len);

    if (1 != EVP_DecryptFinal(ctx, out + out_len, &out_len)) {
        fprintf(stderr,"EVP_DecrypFinal failed\n");
    }
    if (out_len) fprintf(stderr, "final wrote %d bytes\n", out_len);

    fprintf(stdout, "%s\n", out);

cleanup_ctx:
    EVP_CIPHER_CTX_free(ctx);

key_free:
    free(key);
done:
    free(ct);
    free(out);
}

