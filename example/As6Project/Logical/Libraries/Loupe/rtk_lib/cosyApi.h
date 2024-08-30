/*

Configuration System (COSY) API.

The configuration system handles configuration elements. An element is uniquely
specified by its location and id (also called fqn - fully qualified name). The
separation takes place by '/'.
An element consists of groups, and properties. Groups consist of sub-groups
and properties.

For more information see:
Y:\TuM\BuAsw\BUInfo\Projekte\AT-50-000825_GlobaleSystemArchitektur\Technik\ConfigurationSystemArRegistry\AT-50-000825_TS_ConfigurationSystemAR.docx
Y:\TuM\BuAsw\BUInfo\Projekte\AT-50-000825_GlobaleSystemArchitektur\Technik\ConfigurationSystem\AT-50-000825_TS_ConfigurationSystem.docx

The API is separated in the following parts:
 -> cosyAdminApi.h      - element administration (creation, add members, deletion)
 -> cosyReadApi.h       - read attributes and properties

*/

#ifndef _COSY_API_H_
#define _COSY_API_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* COSY handle */
typedef struct COSY* COSY_H;

/*
 * Returns the handle of an existing COSY element specified by its location and id.
 *
 * return COSY handle for the element, NULL on failure (e.g. non existing).
 */
COSY_H cosyOpenElement(const char* location, const char* id);

/*
 * Returns the handle of an existing COSY element specified by its fqn ("<location>/<id>").
 *
 * return COSY handle for the element, NULL on failure (e.g. non existing).
 */
COSY_H cosyOpenElementByFqn(const char* fqn);

/*
 * Closes a COSY element.
 *
 * Cosy elements can be opend with cosyOpenElement or with cosyCreateElement (cosyWriteApi.h).
 * If the element is non volatile and changes were made, the changes are flushed to the non volatile copy.
 *
 * return true on success, false on failure.
 */
bool cosyCloseElement(COSY_H hCosy);

#ifdef __cplusplus
}
#endif

#endif
