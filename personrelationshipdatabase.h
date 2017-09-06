#ifndef PERSONRELATIONSHIPDATABASE_H
#define PERSONRELATIONSHIPDATABASE_H
#include "json_macros.h"

class PersonRelationshipDatabase {
public:
	object transactionLock;
	const QString PersonQueryBaseCommandSelect = "SELECT DISTINCT targetId FROM relationships AS rel\r\n LEFT OUTER JOIN relationshipdata AS data ON rel.id = data.relationshipId ";
	const QString PersonQueryBaseCommandWhere = " WHERE rel.ownerId = @ownId ";
	const QString PersonQueryFilterBaseCommandSelect = "SELECT rel.id FROM relationships AS rel\r\n LEFT OUTER JOIN relationshipdata AS data ON rel.id = data.relationshipId ";
	const QString PersonQueryFilterBaseCommandWhere = " WHERE rel.ownerId = @ownId AND rel.targetId = @tarId ";
	const QString PersonQueryFilterBaseCommandLimit = " LIMIT 1 ";

	PersonRelationshipDatabase(QJsonObject *d = NULL)
	{
		if (d) init(d);
		transactionLock = RuntimeHelpers.GetObjectValue(new object());
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			// *INDENT-OFF*
			__IF_OBJ_FROM_JSON(it, transactionLock)
			// *INDENT-ON*
		}
	}
	void InitializeTables()
	{
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand pragmaCommand = db.CreateCommand())
			{
				pragmaCommand.CommandText = "PRAGMA cache=shared";
				pragmaCommand.ExecuteNonQuery();
			}
			using (SQLiteCommand createSql = db.CreateCommand())
			{
				createSql.CommandText = "CREATE TABLE relationships ( id INTEGER PRIMARY KEY AUTOINCREMENT, ownerId INTEGER NOT NULL, targetId INTEGER NOT NULL, value DOUBLE NOT NULL DEFAULT 0)";
				createSql.ExecuteNonQuery();
				createSql.CommandText = "CREATE TABLE relationshipdata ( relationshipId INTEGER NOT NULL, dataKey VARCHAR(20) NOT NULL, dataValue INTEGER NOT NULL DEFAULT 0, PRIMARY KEY (relationshipId, dataKey) FOREIGN KEY (relationshipId) REFERENCES relationships(id))";
				createSql.ExecuteNonQuery();
			}
			// }
			catch (SQLiteException expr_70)
			{
				ProjectData.SetProjectError(expr_70);
				SQLiteException ex = expr_70;
				throw new DatabaseException("Error during database initialization.", ex);
			}
		}
	}
	void DeleteTables()
	{
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand dropSql = db.CreateCommand())
			{
				dropSql.CommandText = "DROP TABLE IF EXISTS relationshipdata";
				dropSql.ExecuteNonQuery();
				dropSql.CommandText = "DROP TABLE IF EXISTS relationships";
				dropSql.ExecuteNonQuery();
			}
			// }
			catch (SQLiteException expr_46)
			{
				ProjectData.SetProjectError(expr_46);
				SQLiteException ex = expr_46;
				throw new DatabaseException("Error during database deletion.", ex);
			}
		}
	}
	void AddRelationshipValue(Person owner, Person target, double value)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand updateSql = db.CreateCommand())
			{
				updateSql.CommandText = "UPDATE relationships SET value = value + @value WHERE ownerId = @ownId AND targetId = @tarId";
				updateSql.Parameters.AddWithValue("value", value);
				updateSql.Parameters.AddWithValue("ownId", owner.UID);
				updateSql.Parameters.AddWithValue("tarId", target.UID);
				if (updateSql.ExecuteNonQuery() == 0)
				{
					updateSql.CommandText = "INSERT INTO relationships (ownerId, targetId, value) VALUES (@ownId, @tarId, @value)";
					updateSql.ExecuteNonQuery();
				}
			}
			// }
			catch (SQLiteException expr_B0)
			{
				ProjectData.SetProjectError(expr_B0);
				SQLiteException ex = expr_B0;
				throw new DatabaseException("Error during database update.", ex);
			}
		}
		// }
	}
	void SetRelationshipValue(Person owner, Person target, double value)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand updateSql = db.CreateCommand())
			{
				updateSql.CommandText = "UPDATE relationships SET value = @value WHERE ownerId = @ownId AND targetId = @tarId";
				updateSql.Parameters.AddWithValue("value", value);
				updateSql.Parameters.AddWithValue("ownId", owner.UID);
				updateSql.Parameters.AddWithValue("tarId", target.UID);
				if (updateSql.ExecuteNonQuery() == 0)
				{
					updateSql.CommandText = "INSERT INTO relationships (ownerId, targetId, value) VALUES (@ownId, @tarId, @value)";
					updateSql.ExecuteNonQuery();
				}
			}
			// }
			catch (SQLiteException expr_B0)
			{
				ProjectData.SetProjectError(expr_B0);
				SQLiteException ex = expr_B0;
				throw new DatabaseException("Error during database update.", ex);
			}
		}
		// }
	}
	double GetRelationshipValue(Person owner, Person target)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		double GetRelationshipValue;
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand querySql = db.CreateCommand())
			{
				querySql.CommandText = "SELECT value FROM relationships WHERE ownerId = @ownId AND targetId = @tarId";
				querySql.Parameters.AddWithValue("ownId", owner.UID);
				querySql.Parameters.AddWithValue("tarId", target.UID);
				using (SQLiteDataReader reader = querySql.ExecuteReader())
				{
					if (reader.Read())
					{
						GetRelationshipValue = reader.GetDouble(0) < -100.0 ? -100.0 : (reader.GetDouble(0) > 100.0 ? 100.0 : reader.GetDouble(0));
						return GetRelationshipValue;
					}
				}
			}
			// }
			catch (SQLiteException expr_C0)
			{
				ProjectData.SetProjectError(expr_C0);
				SQLiteException ex = expr_C0;
				throw new DatabaseException("Error during database query.", ex);
			}
		}
		// }
		GetRelationshipValue = 0.0;
		return GetRelationshipValue;
	}
	void AddRelationshipDataDict(Person owner, Person target, QString tag, int value)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand updateSql = db.CreateCommand())
			{
				updateSql.CommandText = "UPDATE relationshipdata SET dataValue = dataValue + @value WHERE relationshipId = (SELECT id FROM relationships                         WHERE ownerId = @ownId                         AND targetId = @tarId) AND dataKey = @key";
				updateSql.Parameters.AddWithValue("key", tag);
				updateSql.Parameters.AddWithValue("value", value);
				updateSql.Parameters.AddWithValue("ownId", owner.UID);
				updateSql.Parameters.AddWithValue("tarId", target.UID);
				if (updateSql.ExecuteNonQuery() == 0)
				{
					updateSql.CommandText = "SELECT id FROM relationships WHERE ownerId = @ownId AND targetId = @tarId";
					long id = -1L;
					using (SQLiteDataReader reader = updateSql.ExecuteReader())
					{
						if (reader.Read())
						{
							id = reader.GetInt64(0);
						}
					}
					if (id >= 0L)
					{
						updateSql.CommandText = "INSERT INTO relationshipdata (relationshipId, dataKey, dataValue) VALUES (@id, @key, @value)";
						updateSql.Parameters.AddWithValue("id", id);
						updateSql.ExecuteNonQuery();
					}
					else
					{
						updateSql.CommandText = "INSERT INTO relationships (ownerId, targetId) VALUES (@ownId, @tarId)";
						updateSql.ExecuteNonQuery();
						updateSql.CommandText = "INSERT INTO relationshipdata (relationshipId, dataKey, dataValue) VALUES ( (SELECT id FROM relationships WHERE ownerId = @ownId AND targetId = @tarId), @key, @value)";
						updateSql.ExecuteNonQuery();
					}
				}
			}
			// }
			catch (SQLiteException expr_13E)
			{
				ProjectData.SetProjectError(expr_13E);
				SQLiteException ex = expr_13E;
				throw new DatabaseException("Error during database update.", ex);
			}
		}
		// }
	}
	void SetRelationshipDataDict(Person owner, Person target, QString tag, int value)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand updateSql = db.CreateCommand())
			{
				updateSql.CommandText = "UPDATE relationshipdata SET dataValue = @value WHERE relationshipId = (SELECT id FROM relationships                         WHERE ownerId = @ownId                         AND targetId = @tarId) AND dataKey = @key";
				updateSql.Parameters.AddWithValue("key", tag);
				updateSql.Parameters.AddWithValue("value", value);
				updateSql.Parameters.AddWithValue("ownId", owner.UID);
				updateSql.Parameters.AddWithValue("tarId", target.UID);
				if (updateSql.ExecuteNonQuery() == 0)
				{
					updateSql.CommandText = "SELECT id FROM relationships WHERE ownerId = @ownId AND targetId = @tarId";
					long id = -1L;
					using (SQLiteDataReader reader = updateSql.ExecuteReader())
					{
						if (reader.Read())
						{
							id = reader.GetInt64(0);
						}
					}
					if (id >= 0L)
					{
						updateSql.CommandText = "INSERT INTO relationshipdata (relationshipId, dataKey, dataValue) VALUES (@id, @key, @value)";
						updateSql.Parameters.AddWithValue("id", id);
						updateSql.ExecuteNonQuery();
					}
					else
					{
						updateSql.CommandText = "INSERT INTO relationships (ownerId, targetId) VALUES (@ownId, @tarId)";
						updateSql.ExecuteNonQuery();
						updateSql.CommandText = "INSERT INTO relationshipdata (relationshipId, dataKey, dataValue) VALUES ( (SELECT relationships.id FROM relationships WHERE ownerId = @ownId AND targetId = @tarId), @key, @value)";
						updateSql.ExecuteNonQuery();
					}
				}
			}
			// }
			catch (SQLiteException expr_13E)
			{
				ProjectData.SetProjectError(expr_13E);
				SQLiteException ex = expr_13E;
				throw new DatabaseException("Error during database update.", ex);
			}
		}
		// }
	}
	void AddRelationshipDataDictBitfield(Person owner, Person target, QString tag, int value)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand updateSql = db.CreateCommand())
			{
				updateSql.CommandText = "UPDATE relationshipdata SET dataValue = dataValue | @value WHERE relationshipId = (SELECT id FROM relationships                         WHERE ownerId = @ownId                         AND targetId = @tarId) AND dataKey = @key";
				updateSql.Parameters.AddWithValue("key", tag);
				updateSql.Parameters.AddWithValue("value", value);
				updateSql.Parameters.AddWithValue("ownId", owner.UID);
				updateSql.Parameters.AddWithValue("tarId", target.UID);
				if (updateSql.ExecuteNonQuery() == 0)
				{
					updateSql.CommandText = "SELECT id FROM relationships WHERE ownerId = @ownId AND targetId = @tarId";
					long id = -1L;
					using (SQLiteDataReader reader = updateSql.ExecuteReader())
					{
						if (reader.Read())
						{
							id = reader.GetInt64(0);
						}
					}
					if (id >= 0L)
					{
						updateSql.CommandText = "INSERT INTO relationshipdata (relationshipId, dataKey, dataValue) VALUES (@id, @key, @value)";
						updateSql.Parameters.AddWithValue("id", id);
						updateSql.ExecuteNonQuery();
					}
					else
					{
						updateSql.CommandText = "INSERT INTO relationships (ownerId, targetId) VALUES (@ownId, @tarId)";
						updateSql.ExecuteNonQuery();
						updateSql.CommandText = "INSERT INTO relationshipdata (relationshipId, dataKey, dataValue) VALUES ( (SELECT relationships.id FROM relationships WHERE ownerId = @ownId AND targetId = @tarId), @key, @value)";
						updateSql.ExecuteNonQuery();
					}
				}
			}
			// }
			catch (SQLiteException expr_13E)
			{
				ProjectData.SetProjectError(expr_13E);
				SQLiteException ex = expr_13E;
				throw new DatabaseException("Error during database update.", ex);
			}
		}
		// }
	}
	int GetRelationshipDataDict(Person owner, Person target, QString tag)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		int GetRelationshipDataDict;
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand querySql = db.CreateCommand())
			{
				querySql.CommandText = "SELECT dataValue FROM relationshipdata AS data INNER JOIN relationships AS rel ON data.relationshipId = rel.id WHERE rel.ownerId = @ownId AND rel.targetId = @tarId AND data.dataKey = @key";
				querySql.Parameters.AddWithValue("key", tag);
				querySql.Parameters.AddWithValue("ownId", owner.UID);
				querySql.Parameters.AddWithValue("tarId", target.UID);
				using (SQLiteDataReader reader = querySql.ExecuteReader())
				{
					if (reader.Read())
					{
						GetRelationshipDataDict = reader.GetInt32(0);
						return GetRelationshipDataDict;
					}
				}
			}
			// }
			catch (SQLiteException expr_BB)
			{
				ProjectData.SetProjectError(expr_BB);
				SQLiteException ex = expr_BB;
				throw new DatabaseException("Error during database query.", ex);
			}
		}
		// }
		GetRelationshipDataDict = 0;
		return GetRelationshipDataDict;
	}
	bool TagExists(Person owner, Person target, QString tag)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		bool TagExists;
		// lock (obj) {
		if (db != NULL)
		{
			// try {
			using (SQLiteCommand querySql = db.CreateCommand())
			{
				querySql.CommandText = "SELECT count(*) FROM relationshipdata AS data INNER JOIN relationships AS rel ON data.relationshipId = rel.id WHERE rel.ownerId = @ownId AND rel.targetId = @tarId AND data.dataKey = @key";
				querySql.Parameters.AddWithValue("key", tag);
				querySql.Parameters.AddWithValue("ownId", owner.UID);
				querySql.Parameters.AddWithValue("tarId", target.UID);
				using (SQLiteDataReader reader = querySql.ExecuteReader())
				{
					if (reader.Read())
					{
						TagExists = (reader.GetInt32(0) > 0);
						return TagExists;
					}
				}
			}
			// }
			catch (SQLiteException expr_BE)
			{
				ProjectData.SetProjectError(expr_BE);
				SQLiteException ex = expr_BE;
				throw new DatabaseException("Error during database query.", ex);
			}
		}
		// }
		TagExists = false;
		return TagExists;
	}
	QString ExecuteCommand(QString sql)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// checked {
		QString ExecuteCommand;
		// lock (obj) {
		if (db == NULL)
		{
			ExecuteCommand = "Database has not been initialized yet!";
		}
		else
		{
			sql = sql.Trim();
			// try {
			using (SQLiteCommand command = db.CreateCommand())
			{
				command.CommandText = sql;
				if (sql.StartsWith("SELECT", StringComparison.InvariantCultureIgnoreCase))
				{
					StringBuilder sb = new StringBuilder();
					using (SQLiteDataReader reader = command.ExecuteReader())
					{
						int columnCount = reader.VisibleFieldCount;
						for (int i = 0; i < columnCount; i++)
						{
							sb.append(reader.GetName(i));
							if (i != columnCount - 1)
							{
								sb.append("\t|\t");
							}
						}
						while (reader.Read())
						{
							sb.AppendLine();
							for (int i = 0; i < columnCount; i++)
							{
								sb.append(RuntimeHelpers.GetObjectValue(reader.GetValue(i)));
								if (i != columnCount - 1)
								{
									sb.append("\t|\t");
								}
							}
						}
					}
					ExecuteCommand = sb.ToString();
				}
				else
				{
					ExecuteCommand = "Executed. " + Conversions.ToString(command.ExecuteNonQuery()) + " rows affected.";
				}
			}
			// }
			catch (Exception expr_133)
			{
				ProjectData.SetProjectError(expr_133);
				Exception ex = expr_133;
				ExecuteCommand = "An error occurred: " + ex.Message;
				ProjectData.ClearProjectError();
			}
		}
		// }
		return ExecuteCommand;
		// }
	}
	XmlSchema GetSchema()
	{
		return NULL;
	}
	void WriteXml(XmlWriter writer)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (db != NULL)
		{
			writer.WriteStartElement("Tables");
			SerializeTable(writer, "relationships");
			SerializeTable(writer, "relationshipdata");
			writer.WriteEndElement();
		}
		// }
	}
	void ReadXml(XmlReader reader)
	{
		object obj = transactionLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (db != NULL)
		{
			DeleteTables();
			InitializeTables();
			bool arg_38_0 = reader.IsEmptyElement;
			reader.Read();
			if (!arg_38_0)
			{
				reader.ReadStartElement("Tables");
				DeserializeTables(reader);
				reader.ReadEndElement();
			}
		}
		// }
	}
};

#endif // PERSONRELATIONSHIPDATABASE_H
