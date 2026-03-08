#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

void initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // we use SQLite

    // Database path (in user's local folder)
    QString dataFolder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataFolder);
    if (!dir.exists()) {
        dir.mkpath("."); // Create the folder if not exists
    }
    db.setDatabaseName(dataFolder + "/nomos.sqlite");

    // Open DB
    if (!db.open()) {
        qCritical() << "ERROR : Cannot open the database" << db.lastError().text();
        return;
    }

    // ======== TABLES CREATION ========
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;"); // turn on foreign keys use

    // Student table
    query.exec(
        "CREATE TABLE IF NOT EXISTS student ("
        "id_student INTEGER PRIMARY KEY AUTOINCREMENT, "
        "first_name TEXT NOT NULL, "
        "last_name TEXT NOT NULL, "
        "gender TEXT, "
        "grade_level TEXT NOT NULL" // CP, CE1, CE2, CM1, CM2
        "skill_level INTEGER, " // -1 / 0 / 1
        "behavior_level INTEGER, "
        "autonomy_level INTEGER)"
    );

    // Affinity table
    query.exec(
        "CREATE TABLE IF NOT EXISTS affinity ("
        "id_affinity INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_a_id INTEGER NOT NULL, "
        "student_b_id INTEGER NOT NULL, "
        "type TEXT NOT NULL, "
        "weight INTEGER NOT NULL, "
        "FOREIGN KEY(student_a_id) REFERENCES student(id_student) ON DELETE CASCADE, "
        "FOREIGN KEY(student_b_id) REFERENCES student(id_student) ON DELETE CASCADE )"
    );

    // Scenario table
    query.exec(
        "CREATE TABLE IF NOT EXISTS scenario ("
        "id_scenario INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "is_favorite INTEGER NOT NULL DEFAULT 0, " // boolean
        "score INTEGER, "
        "created_at INTEGER)"
    );

    // Classroom table
    query.exec(
        "CREATE TABLE IF NOT EXISTS classroom ("
        "id_classroom INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "grade_level TEXT, "
        "scenario_id INTEGER NOT NULL, "
        "FOREIGN KEY(scenario_id) REFERENCES scenario(id_scenario) ON DELETE CASCADE )"
    );

    // Allocation table
    query.exec(
        "CREATE TABLE IF NOT EXISTS allocation ("
        "student_id INTEGER NOT NULL, "
        "classroom_id INTEGER NOT NULL, "
        "PRIMARY KEY(student_id, classroom_id), "
        "FOREIGN KEY(student_id) REFERENCES student(id_student) ON DELETE CASCADE, "
        "FOREIGN KEY(classroom_id) REFERENCES classroom(id_classroom) ON DELETE CASCADE )"
    );

    qDebug() << "SUCCESS : the database has been initialized";
}
