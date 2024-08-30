/*

Configuration System (COSY) write API.

This API provides functions:
 - to create and delete COSY members (elements, groups),
 - to set properties,
 - to set the attributes of an element.

Detailed description see cosyApi.h!

*/

#ifndef _COSY_WRITE_API_H_
#define _COSY_WRITE_API_H_
#include <stddef.h>
#include <stdint.h>
#include <cosyApi.h>


#ifdef __cplusplus
extern "C" {
#endif

#define COSY_TIMEOUT_NO_WAIT 0
#define COSY_TIMEOUT_WAIT_FOREVER 0xFFFFFFFF



/*
 * Creates a new COSY element.
 *
 * An element is uniquely specified by its location and id. The result of
 * the combination of location and id is called fqn (fully qualified name).
 * E.g. "System/GMC/Axis" where "System/GMC" is the location and "Axis" is
 * the id of the element. The separation takes place by '/', so an id must not
 * contain a slash.
 *
 * return COSY handle for the element, NULL on failure.
 */
COSY_H cosyCreateElement(const char* location, const char* id, const char* type, const char* technologyPackage);

/*
 * Destroys an existing COSY element.
 *
 * Also, an existing non volatile copy is deleted.
 *
 * return true if deletion succeeds, false on failure.
 */
bool cosyDestroyElement(const char* location, const char* id);

/*
 * Makes a non volatile copy of a COSY element.
 *
 * Must be called again, if changes in an element should be stored non volatile.
 *
 * return true on success, false on failure.
 */
bool cosySaveElement(COSY_H hCosy);

/*
 * Adds a group.
 *
 * It is possible to add subgroups at once. So id can be given as path to a
 * subgroup. Example: if id equals "g1/g2/g3" and none of the groups exists,
 * all groups will be created.
 *
 * return true if add group succeeds, false on failure.
 */
bool cosyAddGroup(COSY_H hCosy, const char* id, const char* value);

/*
 * Sets the value of a group.
 *
 * It is only possible to change values of a group. Set the value to NULL is also not possible.
 *
 * return pointer to the new value string of a group, NULL on failure.
 */
const char* cosySetGroupValue(COSY_H hCosy, const char* id, const char* value);

/*
 * Sets a property value.
 *
 * If the property does not exist it will be created. If the property exists
 * the value will be changed. It is not possible to change the type of an
 * existing property.
 * It is possible to add properties of currently not existing subgroups. So id
 * can be given as path to a property of a subgroup. Example: if id equals "g1/g2/g3/property"
 * and none of the groups exists, all groups will be created.
 *
 * Type mapping (IEC -> type of the given value pointer):
 * BOOL          -> int
 * SINT          -> int
 * INT           -> int
 * DINT          -> int
 * USINT         -> int
 * UINT          -> int
 * UDINT         -> int
 * BYTE          -> int
 * WORD          -> int
 * DWORD         -> int
 * REAL          -> String
 * LREAL         -> String
 * STRING        -> String
 * TIME          -> String
 * DATE          -> String
 * DATE_AND_TIME -> String
 * TIME_OF_DAY   -> String
 * ULINT         -> not supported
 * LWORD         -> not supported
 * WSTRING       -> not supported
 * OCTET         -> not supported
 * LINT          -> not supported
 *
 * return true if set property succeeds, false on failure.
 */
bool cosySetProperty(COSY_H hCosy, const char* id, const char* iecType, const void* pValue, size_t valueSize);

/*
 * Deletes a group or property.
 *
 * Removes a member of an element (group or property) and all its sub-
 * members. A timeout [usec] can be specified, to wait for an
 * opened member:
 * -> COSY_TIMEOUT_NO_WAIT (0) - don't wait,
 * -> COSY_TIMEOUT_WAIT_FOREVER (0xFFFFFFFF) -  wait forever.
 *
 * return true if deletion succeeds, false on failure.
 */
bool cosyDeleteMember(COSY_H hCosy, const char* id, uint32_t timeoutUsec);

/*
 * Sets the version of a COSY element.
 *
 * return true on success, false on failure.
 */
bool cosySetElementVersion(COSY_H hCosy, const char* version);


#if AR_CORE
#include <private/cosyWriteApiP.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
