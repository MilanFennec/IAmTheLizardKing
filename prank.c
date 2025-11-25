#include <ao/ao.h>
#include <mpg123.h>
#include <stdio.h>
#include <stdlib.h>

#define BITS 8

int main() {
  const char *filename = "dude.mp3";
  FILE *file;
  file = fopen(filename, "r");
  if (file == NULL) {
	const char *url = "https://github.com/MilanFennec/IAmTheLizardKing/raw/refs/heads/main/dude.mp3";
	const char *output_file = "dude.mp3";
	char command[256];
	snprintf(command, sizeof(command), "wget -O %s  %s", output_file, url);
	int status = system(command);
     }
    char x[] = "dude.mp3";
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;
    int driver;
    ao_device *dev;
    ao_sample_format format;
    int channels, encoding;
    long rate;
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
    mpg123_open(mh, x);
    mpg123_getformat(mh, &rate, &channels, &encoding);
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        ao_play(dev, buffer, done);
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();

    return 0;

}
