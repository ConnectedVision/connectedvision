/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* Skeleton_output_Average.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "Skeleton_output_Average";
CREATE TABLE "Skeleton_output_Average"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* first detection (integer) */,
	'color.R' BIGINT /* red (integer) */,
	'color.G' BIGINT /* green (integer) */,
	'color.B' BIGINT /* blue (integer) */
);
