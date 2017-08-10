{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.stubHeaderPath}}
// NEVER TOUCH this file!

#ifndef {{StoreSQLite.stubName}}_def
#define {{StoreSQLite.stubName}}_def

#include <stdint.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <ConnectedVision.h>
#include <DBConnection.h>
#include <IStore.h>
#include <general.h>
#include <DataHandling/Store_SQLite_BaseClass.h>
#include <DataHandling/Store_Manager_Basic.h>

// include classes
{% for c in StoreSQLite.table.objectBindings %}{% if c.classHeaderPath %}
#include "{{global.relativeStubToSrcPath}}{{c.classHeaderPath}}"
{% endif %}{% endfor %}

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: {{StoreSQLite.className}}
 *
 * module: {{global.moduleName}}
 * description: {{DataClass.description}}
 */
class {{StoreSQLite.stubName}} :
	public ConnectedVision::DataHandling::Store_SQLite_BaseClass<{{DataClass.className}}>
{

public:
	/**
	* constructor
	*/
	{{StoreSQLite.stubName}}(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	);

	/**
	* virtual desctructor
	*/
	virtual ~{{StoreSQLite.stubName}}();

#ifdef ENABLE_SQLITE_SEARCH
public:
	// additional search functions
{% for c in StoreSQLite.table.columns %}
{% if c.isSearchable %}
	/**
	*  Get objects filtered by {{c.id}}
	*/
	virtual std::vector<shared_ptr<const {{DataClass.className}}> > getBy_{{c.id}}(const {{c.CType}}& val);
{% endif %}
{% endfor %}
#endif

protected:
	// internal functions

	/**
	* read Object from DB
	* @note This function is MANDATORY.
	*
	*	Read table colum fields to object member variables.
	*	Call sqlite3_step() to read all sub/child objects.
	*
	* @return SQLite return code
	*/
	virtual int readObject(
		sqlite3_stmt *stmt,							///< [in] pre-executed SQLite statement
		shared_ptr<const {{DataClass.className}}>& outObj,	///< [out] data object read from DB
		sqlite3 *db									///< [in] SQLite DB object
	);

	/**
	* write Object to DB
	* @note This function is MANDATORY.
	*
	*	Bind object member variables to table colum fields.
	*	This function has to write the whole objects,
	*	i.e. ti has to loop over all sub/child object bind them and call sqlite3_step() for each row.
	*
	* @return SQLite return code
	*/
	virtual int writeObject(
		sqlite3_stmt *stmt,							///< [in] prepared SQLite statement
		const shared_ptr<const {{DataClass.className}}>& obj,	///< [in] data object read from DB
		sqlite3 *db,								///< [in] SQLite DB object
		const int64_t sortID						///< [in] unique index of object
	);

	/**
	* append object internal sort criteria to list
	* @note This function is MANDATORY.
	*/
	virtual void appendObjectGrouping(
		std::vector< Store::SortEntry >& sortList ///< [in/out] list of sort criteria for table rows
	) const;

	/**
	* get name of internal sort criteria column
	* @note This function is MANDATORY.
	*
	* @return column name
	*/
	virtual const std::string objectKey() const;

	// bind functions
{% for b in StoreSQLite.table.objectBindings %}
	/**
	* bind object values for writing
	*/
	virtual void bind_{{b.bindingName}}(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const {{b.CConstType}}& obj,					///< [in] data object read from DB
		const int64_t sortID {% for i in b.idxKeys %},	///< [in] unique index of object
		const int64_t idx{{loop.index}} {% endfor %}	///< [in] sub array index to order sub items
	) const;
{% endfor %}
};

// --> Do NOT EDIT <--
/**
 * factory for: {{StoreSQLite.className}}
 */
class {{StoreSQLite.factoryStubName}} :
	public ConnectedVision::DataHandling::IStore_ReadWrite_Factory<{{DataClass.className}}>
{
public:
	/**
	* constructor
	*	uses DataAllocator_Primitive (new / delete for every object request)
	*/
	{{StoreSQLite.factoryStubName}}(
		DBConnection& db			///< [in] DB connection object
	);

	/**
	* virtual desctuctor
	*/
	virtual ~{{StoreSQLite.factoryStubName}}();

	/**
	* creates a new store
	*/
	virtual shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<{{DataClass.className}}> > create(
		const id_t configID			///< [in] config ID of requested store (optional)
	);

protected:
	DBConnection& db;
};

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#endif // {{StoreSQLite.stubName}}_def