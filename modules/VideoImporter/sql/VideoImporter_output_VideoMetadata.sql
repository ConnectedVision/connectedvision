/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* VideoImporter_output_VideoMetadata.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "VideoImporter_output_VideoMetadata";
CREATE TABLE "VideoImporter_output_VideoMetadata"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* Object ID (string) */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /* job / config ID (string) */,
	'filename' TEXT NOT NULL DEFAULT '' /* filename (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* start time (integer) */,
	'lasttimestamp' BIGINT NOT NULL DEFAULT '0' /* end time (integer) */,
	'width' BIGINT NOT NULL DEFAULT '0' /* width of video in pixels (integer) */,
	'height' BIGINT NOT NULL DEFAULT '0' /* height of video in pixels (integer) */,
	'numberofframes' BIGINT NOT NULL DEFAULT '0' /* number of frames in video (integer) */,
	'fps' DOUBLE NOT NULL DEFAULT '0' /* number of frames per second (number) */
);
