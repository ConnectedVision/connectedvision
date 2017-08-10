/* auto-generated header by CodeFromTemplate */
/* CodeFromTemplate Version: 0.3 alpha */
/* HostStatus.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "HostStatus";
CREATE TABLE "HostStatus"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'hostID' VARCHAR(32) NOT NULL DEFAULT '' /* host id (string) */,
	'systemID' VARCHAR(32) NOT NULL DEFAULT '' /* system ID (string) */,
	'configID' VARCHAR(32) /* virtual config id (string) */,
	'timestamp' BIGINT /* virtual timestamp (integer) */
);
