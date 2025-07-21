# cqp-unit-tests

`cqp-unit-tests` runs through the [Collision Query Protocol](https://github.com/igni-project/cqp), one request at a time. This program generates a consistent set of collision queries for developers to test against their own software.

## Usage

To test a connection, enter the command `cqp_unit_tests` followed by the domain address(es) of the socket you wish to test.

For example: `cqp_unit_tests /run/user/$UID/cqp1 /run/user/$UID/cqp2`

