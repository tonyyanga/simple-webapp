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

func Server(w http.ResponseWriter, req *http.Request) {
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
	flag.StringVar(&dbPassword, "pass", "", "Username of the mysql server")
	flag.StringVar(&dbName, "db", "", "Username of the mysql server")
	flag.Parse()

	//A golang db connection pool
	db, _ = sql.Open("mysql", dbUsername+":"+dbPassword+"@/"+dbName)
	if err := db.Ping(); err != nil {
		log.Fatalf("Error connecting to the mysql database: %s", err)
	}

	http.HandleFunc("/", Server)
	log.Fatal(http.ListenAndServe("127.0.0.1:8000", nil))
}
