/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* generic_moduleStatus.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "generic_moduleStatus";
CREATE TABLE "generic_moduleStatus"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'name' TEXT NOT NULL DEFAULT '' /* module name (string) */,
	'moduleID' VARCHAR(32) NOT NULL DEFAULT '' /* ID of module (string) */,
	'moduleStatus' TEXT NOT NULL DEFAULT '' /* current status of module (string) */,
	'configsRunning._idx1' BIGINT /* array index dimension: 1 (array) */,
	'configsRunning' VARCHAR(32) /* config ID (string) */,
	'configsWaiting._idx1' BIGINT DEFAULT '' /* array index dimension: 1 (array) */,
	'configsWaiting' VARCHAR(32) /* config ID (string) */,
	'configID' VARCHAR(32) /* virtual config id (string) */,
	'timestamp' BIGINT /* virtual timestamp (integer) */
);
