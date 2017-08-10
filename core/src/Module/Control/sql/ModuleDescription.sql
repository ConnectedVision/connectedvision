/* auto-generated header by CodeFromTemplate */
/* CodeFromTemplate Version: 0.3 alpha */
/* ModuleDescription.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "ModuleDescription";
CREATE TABLE "ModuleDescription"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'name' TEXT NOT NULL DEFAULT '' /* module name (string) */,
	'description' TEXT NOT NULL DEFAULT '' /* long description of module (string) */,
	'version' DOUBLE NOT NULL DEFAULT '0' /* version of module (number) */,
	'moduleID' TEXT NOT NULL DEFAULT '' /* unique ID of module (string) */,
	'moduleURI' TEXT NOT NULL DEFAULT '' /* URL of module instance. Will be updated by the module server. (string) */,
	'APIVersion' DOUBLE NOT NULL DEFAULT '0' /* version of supported Connected Vision version (number) */,
	'moduleFeatures.supportsLive' TINYINT /* The module does support live configurations. (boolean) */,
	'moduleFeatures.supportsResume' TINYINT /* The module does support resuming of stopped configurations. (boolean) */,
	'moduleFeatures.supportsDynamicParameters' TINYINT /* The module does support dynamic parameters. (boolean) */,
	'configFeatures.allowDynamicParameters' TINYINT /* the config does support dynamic parameters (boolean) */,
	'author' TEXT NOT NULL DEFAULT '' /* author names of email address (string) */,
	'params.type' TEXT /*  (string) */,
	'configID' VARCHAR(32) /* virtual config id (string) */,
	'timestamp' BIGINT /* virtual timestamp (integer) */
);
