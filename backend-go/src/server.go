package main

import (
	"database/sql"
	"flag"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"log"
	"net/http"
)

var db *sql.DB

func SimpleQueryHandler(w http.ResponseWriter, req *http.Request) {
	// Perform SQL query for a key-value table called "simple" and return results
	rows, err := db.Query("SELECT id, value FROM simple WHERE 1")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	for rows.Next() {
		var id string
		var value string
		if err := rows.Scan(&id, &value); err != nil {
			log.Fatal(err)
		}
		fmt.Fprintf(w, "%s, %s\n", id, value)
	}
	//log.Printf("Query Success!")
}

func main() {
	var dbUsername string
	var dbPassword string
	var dbName string

	// No db address or port specified yet. Using default
	flag.StringVar(&dbUsername, "user", "", "Username of the mysql server")
	flag.StringVar(&dbPassword, "pass", "", "Password for the mysql server account")
	flag.StringVar(&dbName, "db", "", "Name of the mysql database to use")
	flag.Parse()

	//A golang db connection pool
	db, _ = sql.Open("mysql", dbUsername+":"+dbPassword+"@/"+dbName)
	if err := db.Ping(); err != nil {
		log.Fatalf("Error connecting to the mysql database: %s", err)
	}

	http.HandleFunc("/", SimpleQueryHandler)

	// Listen at localhost only to be used by the nginx reverse proxy
	log.Fatal(http.ListenAndServe("127.0.0.1:8000", nil))
}
