# Info
Library is provided by Loupe  
https://loupe.team  
info@loupe.team  
1-800-240-7042  

# Description
This library extends string capabilities. Includes useful tools for parsing strings, formatting data, and converting to/from string to other data formats.

For more documentation and examples, see https://loupeteam.github.io/LoupeDocs/libraries/stringext.html

# Installation
To install using the Loupe Package Manager (LPM), in an initialized Automation Studio project directory run `lpm install stringext`. For more information about LPM, see https://loupeteam.github.io/LoupeDocs/tools/lpm.html

# Self tests

The example project in `example/As6Project` carries table-driven self tests for
some of the library functions. Each is gated by a BOOL in the `Default` program:
set it, and the test runs once on the next cycle and writes its results back.

| Trigger | Covers | Results |
|---|---|---|
| `formatTest` | `formatString()` | `formatTestPass`, `formatTestFail`, `formatTestFirstFail` |
| `hexTest` | `HexStringToUDINT()`, `UDINTToHexString()` | `hexTestPass`, `hexTestFail`, `hexTestFirstFail` |

`...Fail` must come back 0. `...FirstFail` names the first input that did not
behave as expected, and is left empty when the failure was a scalar assertion
rather than a table case.

Build and deploy the `Intel` configuration to ARsim, then set the trigger from
the Automation Studio watch window, or over OPC UA from any client — the four
variables of each suite are published in `OpcUaMap.uad`.

The `Intel` configuration enables the OPC UA server with an unencrypted
endpoint and anonymous access, so that the self tests can be driven without
credentials. That is appropriate for this example project, which exists to
compile the library and run its tests; **do not copy this OPC UA configuration
into a real machine.**

## Licensing

This project is licensed under the [MIT License](LICENSE). 