/* auto-generated header by CodeFromTemplate */
/* CodeFromTemplate Version: 0.3 alpha */
/* UnitTest_GeneratorTestCode.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "UnitTest_GeneratorTestCode";
CREATE TABLE "UnitTest_GeneratorTestCode"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /* config id (string) */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* object id (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp of object (integer) */,
	'boolVal' TINYINT /* simple boolean value (boolean) */,
	'intVal' BIGINT /* simple integer value (integer) */,
	'numberVal' DOUBLE /* simple float value (number) */,
	'stringVal' TEXT /* simple string value (string) */,
	'anyVal' BLOB /* a generic type should be handled as plan text (any) */,
	'simpleArray._idx1' BIGINT /* array index dimension: 1 (array) */,
	'simpleArray' BIGINT /*  (integer) */,
	'stringArray._idx1' BIGINT /* array index dimension: 1 (array) */,
	'stringArray' TEXT /*  (string) */,
	'intArray._idx1' BIGINT /* array index dimension: 1 (array) */,
	'intArray._idx2' BIGINT /* array index dimension: 2 (array) */,
	'intArray._idx3' BIGINT /* array index dimension: 3 (array) */,
	'intArray' BIGINT /* actual value (integer) */,
	'floatArray._idx1' BIGINT /* array index dimension: 1 (array) */,
	'floatArray._idx2' BIGINT /* array index dimension: 2 (array) */,
	'floatArray._idx3' BIGINT /* array index dimension: 3 (array) */,
	'floatArray' DOUBLE /* actual value (number) */,
	'objArray._idx1' BIGINT /* array index dimension: 1 (array) */,
	'objArray.name' TEXT /*  (string) */,
	'objArray.index' BIGINT /*  (integer) */,
	'objArray.subArray._idx2' BIGINT /* array index dimension: 2 (array) */,
	'objArray.subArray' TEXT /*  (string) */,
	'simpleObject.name' TEXT /*  (string) */,
	'simpleObject.value' BIGINT /*  (integer) */,
	'complexObject.name' TEXT /*  (string) */,
	'complexObject.subObjectArray._idx1' BIGINT /* array index dimension: 1 (array) */,
	'complexObject.subObjectArray._idx2' BIGINT /* array index dimension: 2 (array) */,
	'complexObject.subObjectArray.sub' TEXT /*  (string) */
);
