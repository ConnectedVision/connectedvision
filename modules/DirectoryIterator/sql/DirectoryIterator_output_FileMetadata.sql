/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* DirectoryIterator_output_FileMetadata.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "DirectoryIterator_output_FileMetadata";
CREATE TABLE "DirectoryIterator_output_FileMetadata"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* file ID (string) */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /* job / config ID (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp (integer) */,
	'filePath' TEXT NOT NULL DEFAULT '' /* absolute file path (string) */
);
