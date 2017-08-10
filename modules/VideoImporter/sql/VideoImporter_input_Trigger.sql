/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* VideoImporter_input_Trigger.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "VideoImporter_input_Trigger";
CREATE TABLE "VideoImporter_input_Trigger"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */
);
