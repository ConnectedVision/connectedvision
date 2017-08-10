/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* ThumbnailGenerator_input_BoundingBox.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "ThumbnailGenerator_input_BoundingBox";
CREATE TABLE "ThumbnailGenerator_input_BoundingBox"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* ID (string) */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /* job / config ID (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */,
	'boundingBox.left' DOUBLE /* x position of left side (number) */,
	'boundingBox.right' DOUBLE DEFAULT '1' /* x position of right side (number) */,
	'boundingBox.bottom' DOUBLE DEFAULT '1' /* y position of bottom side (number) */,
	'boundingBox.top' DOUBLE /* y position of top side (number) */
);
