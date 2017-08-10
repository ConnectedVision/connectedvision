/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* SyntheticVideo_output_FrameMetadata.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "SyntheticVideo_output_FrameMetadata";
CREATE TABLE "SyntheticVideo_output_FrameMetadata"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* Object ID (string) */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /* job / config ID (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* start time (integer) */,
	'framenumber' BIGINT NOT NULL DEFAULT '0' /* frame number (integer) */,
	'width' BIGINT NOT NULL DEFAULT '0' /* width of frame in pixels (integer) */,
	'height' BIGINT NOT NULL DEFAULT '0' /* height of frame in pixels (integer) */
);
