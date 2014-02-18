#ifndef __IIO_H__
#define __IIO_H__

#ifdef __GNUC__
#define __pure __attribute__((pure))
#else
#define __pure
#endif

#include <stdlib.h>

enum iio_debug_level {
	DEBUG,
	INFO,
	WARNING,
	ERROR,
};

enum iio_channel_type {
	IIO_CHANNEL_INPUT,
	IIO_CHANNEL_OUTPUT,
	IIO_CHANNEL_UNKNOWN,
};

struct iio_context;
struct iio_device;
struct iio_channel;

/* Top-level functions */
struct iio_context * iio_create_local_context(void);
struct iio_context * iio_create_xml_context(const char *xml_file);
struct iio_context * iio_create_network_context(void *foo);
void iio_context_destroy(struct iio_context *ctx);

/* Context functions */
const char * iio_context_get_name(const struct iio_context *ctx) __pure;
unsigned int iio_context_get_devices_count(
		const struct iio_context *ctx) __pure;
struct iio_device * iio_context_get_device(const struct iio_context *ctx,
		unsigned int index);

/* Device functions */
const char * iio_device_get_id(const struct iio_device *dev) __pure;
const char * iio_device_get_name(const struct iio_device *dev) __pure;
unsigned int iio_device_get_channels_count(
		const struct iio_device *dev) __pure;
struct iio_channel * iio_device_get_channel(const struct iio_device *dev,
		unsigned int index);
unsigned int iio_device_get_attrs_count(const struct iio_device *dev) __pure;
const char * iio_device_get_attr(const struct iio_device *dev,
		unsigned int index) __pure;

/* Channel functions */
const char * iio_channel_get_id(const struct iio_channel *chn) __pure;
const char * iio_channel_get_name(const struct iio_channel *chn) __pure;
enum iio_channel_type iio_channel_get_type(
		const struct iio_channel *chn) __pure;
int iio_channel_enable(struct iio_channel *chn);
int iio_channel_disable(struct iio_channel *chn);
unsigned int iio_channel_get_attrs_count(const struct iio_channel *chn) __pure;
const char * iio_channel_get_attr(const struct iio_channel *chn,
		unsigned int index) __pure;

/* Functions to read/write the raw stream from the device */
ssize_t iio_device_read_raw(const struct iio_device *dev,
		void *dst, size_t len);
ssize_t iio_device_write_raw(const struct iio_device *dev,
		const void *src, size_t len);

/* Functions to read/write the raw stream of a channel
 * (after demux/mux process) */
ssize_t iio_channel_read_raw(const struct iio_channel *chn,
		void *dst, size_t len);
ssize_t iio_channel_write_raw(const struct iio_channel *chn,
		const void *src, size_t len);

/* Functions to read/write a stream of converted values from/to a channel */
ssize_t iio_channel_read(const struct iio_channel *chn,
		void *dst, size_t len);
ssize_t iio_channel_write(const struct iio_channel *chn,
		const void *src, size_t len);

/* Device/channel attribute functions */
ssize_t iio_device_attr_read(const struct iio_device *dev,
		const char *attr, char *dst, size_t len);
ssize_t iio_device_attr_write(const struct iio_device *dev,
		const char *attr, const char *src);
ssize_t iio_channel_attr_read(const struct iio_channel *chn,
		const char *attr, char *dst, size_t len);
ssize_t iio_channel_attr_write(const struct iio_channel *chn,
		const char *attr, const char *src);

/* Debug functions */
const struct iio_data_format * iio_channel_get_data_format(
		const struct iio_channel *chn);
unsigned int iio_channel_get_index(const struct iio_channel *chn);
void iio_channel_force_data_format(struct iio_channel *chn,
		const struct iio_data_format *format);
void iio_channel_set_index(struct iio_channel *chn, unsigned int index);

#endif /* __IIO_H__ */
