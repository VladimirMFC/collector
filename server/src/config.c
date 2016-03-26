#include "config.h"

#include <ucl.h>

#include <string.h>

static struct ucl_parser *parser = NULL;

bool config_exist()
{
	if (parser != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool config_open(const char* filename)
{
	bool ret = false;

	if (parser == NULL)
	{
		if ((parser = ucl_parser_new(0)))
		{
			ret = ucl_parser_add_file(parser, filename);
		}
	}

	if (ret && ucl_parser_get_error(parser))
	{
		ucl_parser_free(parser);
		parser = NULL;
		ret = false;
	}

	return ret;
}

bool config_close()
{
	if (parser != NULL)
	{
		ucl_parser_free(parser);
		parser = NULL;
		return true;
	}

	return false;
}

static const ucl_object_t* config_find_key(const char* key)
{
	const ucl_object_t *ret = NULL;

	ucl_object_t *top = NULL;
	if ((top = ucl_parser_get_object(parser)) && (strlen(key) != 0))
	{
		const char dl = '/';
		size_t pos = 0;

		ucl_object_iter_t it = ucl_object_iterate_new(top);
		ret = top;

		while (*key !='\0' && ret != NULL)
		{
			for (pos = 0; key[pos] != '\0' && key[pos] != dl; pos++)
			{
				;
			}

			it = ucl_object_iterate_reset(it, ret);
			ret = NULL;

			const ucl_object_t *cur = NULL;
			while ((cur = ucl_object_iterate_safe(it, true)) != NULL)
			{
				if (strncmp(key, ucl_object_key(cur), pos) == 0)
				{
					ret = cur;
					break;
				}
			}

			if (key[pos] == dl)
			{
				pos++;
			}

			key += pos;
		}

		ucl_object_iterate_free(it);
		ucl_object_unref(top);
	}

	return ret;
}

const char* config_value(const char* key)
{
	const char *ret = NULL;
	const ucl_object_t *obj = config_find_key(key);

	if (obj != NULL)
	{
		ret = ucl_object_tostring_forced(obj);
	}

	return ret;
}

int64_t config_value_int(const char* key)
{
	int ret = 0;
	const ucl_object_t *obj = config_find_key(key);

	if (obj != NULL)
	{
		ret = ucl_object_toint(obj);
	}

	return ret;
}

double config_value_double(const char* key)
{
	double ret = 0.0;
	const ucl_object_t *obj = config_find_key(key);

	if (obj != NULL)
	{
		ret = ucl_object_todouble(obj);
	}

	return ret;
}

bool config_value_bool(const char* key)
{
	bool ret = false;
	const ucl_object_t *obj = config_find_key(key);

	if (obj != NULL)
	{
		ret = ucl_object_toboolean(obj);
	}

	return ret;
}

const char* config_value_string(const char* key)
{
	const char *ret = NULL;
	const ucl_object_t *obj = config_find_key(key);

	if (obj != NULL)
	{
		ret = ucl_object_tostring(obj);
	}

	return ret;
}
