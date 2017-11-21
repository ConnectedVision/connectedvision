/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* generic_config.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "generic_config";
CREATE TABLE "generic_config"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* config ID (string) */,
	'timestamp' BIGINT /* time of modification (integer) */,
	'name' TEXT NOT NULL DEFAULT '' /* config name (string) */,
	'description' TEXT NOT NULL DEFAULT '' /* config description (string) */,
	'aliasID._idx1' BIGINT /* array index dimension: 1 (array) */,
	'aliasID.id' TEXT /* an aliasID to be assigned to this config (string) */,
	'aliasID.timestamp' BIGINT /* creation timestamp of aliasID for this config (integer) */,
	'version' BIGINT NOT NULL DEFAULT '0' /* config version (integer) */,
	'moduleID' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'moduleURI' TEXT NOT NULL DEFAULT '' /* URI of module instance (string) */,
	'configFeatures.allowDynamicParameters' TINYINT /* the config does support dynamic parameters (boolean) */,
	'callback.moduleID' VARCHAR(32) /*  (string) */,
	'callback.moduleURI' TEXT /* URI of module instance (string) */,
	'params' BLOB /*  (any) */,
	'initialParams' BLOB /*  (any) */,
	'chain._idx1' BIGINT /* array index dimension: 1 (array) */,
	'chain.connections._idx2' BIGINT /* array index dimension: 2 (array) */,
	'chain.connections.inputPinID' TEXT /* id of input pin (string) */,
	'chain.connections.outputPinID' TEXT /* id of output pin (string) */,
	'chain.config' BLOB /* config of sub module (any) */,
	'configID' VARCHAR(32) /* virtual config id (string) */
);
