/* pvElementIteratorApi
 * This API provides functions to get all elements that a pv is composed of
 * for each leaf-element one callback will occur e.g.:
 * 
 * TYPE
 *	TestStruct : 	STRUCT 
 *		Struct_Bool : BOOL := 1;
 *		Struct_Dint : DINT := -2000000000;
 *		Struct_DT : DATE_AND_TIME := DT#1992-09-23-20:15:00;
 *		Struct_Int : INT := -3000;
 *		Struct_LReal : LREAL := -1234567.12345;
 *	END_STRUCT;
 *	FARBEN : 
 *	(
 *		GRUEN,
 *		TUERKIS,
 *		LILA
 *	);
 *	adt_basic_bool : BOOL;
 * END_TYPE
 * 
 * VAR
 * 	var_Struct : TestStruct;
 * 	var_Sint : SINT;
 * 	pvArray_adt_basic_bool : ARRAY[-32001..-32000] OF adt_basic_bool;
 * 	rb1 : REFERENCE TO BOOL;
 * 	var_colour : FARBEN;
 * END_VAR
 * 
 * pveiIterateElements("TestStruct",...)
 * name				address 	size	type
 * .Struct_Bool     0x5bf3c24 	1		BOOL
 * .Struct_Dint     0x5bf3c28 	4		DINT
 * .Struct_DT   	0x5bf3c2c 	4		DATE_AND_TIME
 * .Struct_Int 		0x5bf3c30 	2		INT
 * .Struct_LReal    0x5bf3c34 	8		LREAL
 * 
 * pveiIterateElements("var_Sint",...)
 * name				address 	size	type
 * (emty)			0x56e3fcd	1		SINT
 * 
 * pveiIterateElements("pvArray_adt_basic_bool",...)
 * name				address 	size	type	baseType
 * [-32001]			0x56e3f68	1		INVALID BOOL
 * [-32000]			0x56e3f69	1		INVALID BOOL
 * 
 * pveiIterateElements("rb1",...)
 * name				address 	size	type	baseType	isRefernce	BaseAddr	Offset
 * (emty)			NULL		1		INVALID	BOOL		true		0x5aca396	0
 * 
 * pveiIterateElements("var_colour",...)
 * name				address 	size	type	baseType	isEnum
 * (emty)			0x56e3f6c	4		INVALID	INVALID		true 
 */

#ifndef _PVEI_API_H_
#define _PVEI_API_H_

#include <iecType.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PVELEM* PVELEM_H;
typedef struct ENUMVAL* ENUMVAL_H;

/* Callback for each element within a PV.
 * The parameter 'pvElem' is a handle to the current element that can be used to get further 
 * information. It is only valid for the duration of the callback.
 * The Parameter 'pArg' is the pointer 'pCallbackArg' that was provided to pveiIterateElements().
 * Return true to continue the iteration, false to stop. 
 */
typedef bool (*PVEI_CALLBACK_FP)(PVELEM_H pvElem, void* pArg);

/* 
 * Find a PV by name and call a function for each leaf element of the PV and
 * for each leaf element of substructures to any depth.
 * One callback occurs for every member of an array.
 * Basic PVs are considered to have one nameless member.
 * Syntax for 'pvName': (see 'Names of process variables' in AS help):
 * [<appModule>"::"][<object name>":"]<PV name>["["<number>"]"]["."<element name>]
 * <appModule> Name of the application module (optional).
 * <Object Name> Name of the cyclic object (optional).
 * <PV name> Name of the process variable.
 * <Number> Index of the array element (optional).
 * <ElementName> Name of the structure element (optional).
 * 'pvName' must not be NULL.
 * 'fpCallback' can be NULL.
 * 'pCallbackArg' can be NULL.
 * True is returned when the PV was found, false otherwise.
 */
bool pveiIterateElements(const char pvName[], PVEI_CALLBACK_FP fpCallback, void* pCallbackArg);

/* 
 * Returns true if the 'nameBuffer' holds the name and the path to the element, 
 * false if the supplied buffer was too small.
 * The name of the PV that is being iterated is not part of the returned name.
 * If the PV has no subelements (it is an IEC base type or a direct derived type) nameBuffer will be empty.
 * 'pvElem' must not be NULL.
 * 'nameBuffer' must not be NULL.
 * 'nameBufferSize' must hold the size of 'nameBuffer'.
 */
bool pveiGetName(PVELEM_H pvElem, char nameBuffer[], unsigned int nameBufferSize);

/* 
 * Returns the IEC type of an element.
 * If IEC_TYPE_INVALID is returned the element is a user defined type.
 * E.g. an enum or a direct derived type or an element that is accessed via a reference.
 * 'pvElem' must not be NULL.
 */
IEC_TYPE pveiGetType(PVELEM_H pvElem);

/* 
 * Returns the base IEC type of a direct derived type or an element that is accessed via a reference.
 * Returns IEC_TYPE_INVALID for base types and enum.
 * 'pvElem' must not be NULL.
 */
IEC_TYPE pveiGetBaseType(PVELEM_H pvElem);

/* 
 * Returns the size in bytes of the element or 0 in case of an error.
 * For IEC base types this function is identical to iecTypeSize() for
 * other types the size is depending on the implementation.
 * 'pvElem' must not be NULL.
 */
unsigned int pveiGetSize(PVELEM_H pvElem);

/* 
 * Returns the address of the element.
 * NULL is returned when the element is accessed via a reference.
 * The value of the element can be read with *(address).
 * 'pvElem' must not be NULL.
 */
void* pveiGetAddr(PVELEM_H pvElem);

/* 
 * Returns the base address of an element that is accessed via a reference.
 * Returns in 'offset' the number of bytes that need to be added 
 * to the content of the base address to get the value of the element.
 * The value of the element can be read with *(*(baseAddress) + 'offset')
 * 'pvElem' must not be NULL.
 * 'offset' can be NULL.
 */
void* pveiGetBaseAddrAndOffset(PVELEM_H pvElem, unsigned int* offset);

/* 
 * Returns true if the element is accessed via a reference.
 * 'pvElem' must not be NULL.
 */
bool pveiIsReferenceTo(PVELEM_H pvElem);

/* 
 * Returns true if the element is an enum.
 * 'pvElem' must not be NULL.
 */
bool pveiIsEnum(PVELEM_H pvElem);

/* 
 * Callback for each valid value of an enum.
 * The parameter 'enumVal' is a handle that can be used to retrive the properties of the enum entry.
 * It is only valid for the duration of the callback.
 * The Parameter 'pArg' is the pointer 'pCallbackArg' that was provided to pveiIterateEnumValues().
 * Return true to continue the iteration, false to stop.
 */
typedef bool (*PVEI_ENUM_CALLBACK_FP)(ENUMVAL_H enumVal, void* pArg);

/* 
 * Call a function for each valid value of an enum.
 * 'pvElem' must not be NULL. 
 * 'fpCallback' must not be NULL.
 * 'pCallbackArg' can be NULL.
 */
void pveiIterateEnumValues(PVELEM_H pvElem, PVEI_ENUM_CALLBACK_FP fpCallback, void* pCallbackArg);

/* 
 * Returns the numeric representation of the enum value.
 * 'enumVal' must not be NULL. 
 */
int pveiEnumGetNumericValue(ENUMVAL_H enumVal);

/* 
 * Returns true if a subrange was set.
 * 'pvElem' must not be NULL. 
 */
bool pveiHasSubrange(PVELEM_H pvElem);

/* 
 * Returns the upper and lower limit of a data type with subrange.
 * 'pvElem' must not be NULL. 
 * 'lowerLimit' can be NULL.
 * 'upperLimit' can be NULL.
 */
void pveiGetSubrangeLimits(PVELEM_H pvElem, int* lowerLimit, int* upperLimit);

#ifdef __cplusplus
}
#endif

#endif
