#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Table {
 public:
  Table(const string& name, const vector<string>& column_names, const vector<vector<string> > data) : name_(name), column_names_(column_names), data_(data) {}

  const string& name() const { return name_; }
  const vector<string>& column_names() const { return column_names_; }
  const vector<vector<string> >& data() const { return data_; }

  // Callee will own the returned pointer
  Table* Select(const vector<string>& column_names) const {
    vector<int> cid;
    for(int i = 0 ; i < column_names.size(); ++i){
        for(int j = 0 ; j < column_names_.size(); ++j){
            if(column_names[i] == column_names_[j]){
                cid.push_back(j);
            }
        }
    }
    vector<vector<string> > ret;
    for(const vector<string>& vs: data_){
        vector<string> row;
        for(int i:cid){
            row.push_back(vs[i]);
        }
        ret.push_back(row);
    }
    vector<string> newCol(column_names.begin(), column_names.end());
    return new Table("Select", newCol, ret);
  }

  // Callee will own the returned pointer
  Table* Where(const string& column_name, const string& value) const {
      int id;
      for(int j = 0 ; j < column_names_.size(); ++j){
            if(column_name == column_names_[j]){
                id = j;
                break;
            }
        }
    vector<vector<string> > ret;
    for(const vector<string>& vs: data_){
        if(vs[id] == value){
            vector<string> row(vs.begin(), vs.end());
            ret.push_back(row);
        }
    }
    vector<string> newCol(column_names_.begin(), column_names_.end());
    return new Table("WhereTable", newCol,ret);
  }

  void Print() {
    string output = JoinStringVector(column_names_);
    for (size_t row_index = 0; row_index < data_.size(); ++row_index) {
      output += JoinStringVector(data_[row_index]);
      output += "\n";
    }
    cout << output << endl;
  }

 private:
  string JoinStringVector(const vector<string>& input) {
    string output = "";
    bool has_data = false;
    for (size_t i = 0; i < input.size(); ++i) {
      has_data = true;
      output += input[i];
      output += ", ";
    }
    if (has_data) {
      output = output.substr(0, output.length() - 2);
    }
    return output;
  }
  const string name_;
  const vector<string> column_names_;
  const vector<vector<string> > data_; // only support string type for simplicity
};


class Database {
 public:
  Database(map<string, const Table*> table_map) : table_map_(table_map) {}
  ~Database() {
    for(map<string, const Table*>::iterator iterator = table_map_.begin(); iterator != table_map_.end(); ++iterator) {
      delete iterator->second;
    }
  }

  const Table* GetTable(const string& table_name) { return table_map_[table_name]; }

  // Callee will own the returned pointer
  Table* InnerJoin(
      const Table* left_table, const string& left_table_key_name,
      const Table* right_table, const string& right_table_key_name) {
    // IMPLEMENT ME
     int id1, id2;
      for(int j = 0 ; j < left_table->column_names().size(); ++j){
            if(left_table_key_name == left_table->column_names()[j]){
                id1 = j;
                break;
            }
        }
        for(int j = 0 ; j < right_table->column_names().size(); ++j){
            if(right_table_key_name == right_table->column_names()[j]){
                id2 = j;
                break;
            }
        }
     vector<vector<string> > ret;
    map<string, vector<vector<string>>> m1, m2;
    
    for(const vector<string>& vs: left_table->data()){
        m1[vs[id1]].push_back(vs);
    }
    for(const vector<string>& vs: right_table->data()){
        m2[vs[id2]].push_back(vs);
    }
    auto iter1 = m1.begin();
    auto iter2 = m2.begin();
    while(iter1 != m1.end() && iter2 != m2.end()){
        if(iter1->first == iter2->first){
            for(const vector<string>& vs1: iter1->second){
                for(const vector<string>& vs2: iter2->second){
                    vector<string> row(vs1.begin(), vs1.end());
                    row.insert(row.end(), vs2.begin(), vs2.end());
                    ret.push_back(row);
                }
            }
            iter1++; iter2++;
        }else if(iter1->first < iter2->first){
            iter1++;
        }else{
            
            iter2++;
        }
    }
   
    
    vector<string> newCol;
    for(int k = 0 ; k < left_table->column_names().size(); ++k){
        newCol.push_back(left_table->name() + "." + left_table->column_names()[k]);
    }
    for(int k = 0 ; k < right_table->column_names().size(); ++k){
        newCol.push_back(right_table->name() + "." + right_table->column_names()[k]);
    }   
    return new Table("InnerJoin", newCol, ret);
  }

  // Callee will own the returned pointer
  Table* LeftJoin(
      const Table* left_table, const string& left_table_key_name,
      const Table* right_table, const string& right_table_key_name) {
    // IMPLEMENT ME
    int id1, id2;
      for(int j = 0 ; j < left_table->column_names().size(); ++j){
            if(left_table_key_name == left_table->column_names()[j]){
                id1 = j;
                break;
            }
        }
        for(int j = 0 ; j < right_table->column_names().size(); ++j){
            if(right_table_key_name == right_table->column_names()[j]){
                id2 = j;
                break;
            }
        }
     vector<vector<string> > ret;
    map<string, vector<vector<string>>> m1, m2;
    
    for(const vector<string>& vs: left_table->data()){
        m1[vs[id1]].push_back(vs);
    }
    for(const vector<string>& vs: right_table->data()){
        m2[vs[id2]].push_back(vs);
    }
    auto iter1 = m1.begin();
    auto iter2 = m2.begin();
    while(iter1 != m1.end() && iter2 != m2.end()){
        if(iter1->first == iter2->first){
            for(const vector<string>& vs1: iter1->second){
                for(const vector<string>& vs2: iter2->second){
                    vector<string> row(vs1.begin(), vs1.end());
                    row.insert(row.end(), vs2.begin(), vs2.end());
                    ret.push_back(row);
                }
            }
            iter1++; iter2++;
        }else if(iter1->first < iter2->first){
            for(const vector<string>& vs1: iter1->second){
                vector<string> row(vs1.begin(), vs1.end());
                for(int k = 0 ; k < right_table->column_names().size(); ++k){
                    row.push_back("");
                }
                ret.push_back(row);
            }
            iter1++;
        }else{
            
            iter2++;
        }
    }
    while(iter1 != m1.end() ){
          for(const vector<string>& vs1: iter1->second){
                vector<string> row(vs1.begin(), vs1.end());
                for(int k = 0 ; k < right_table->column_names().size(); ++k){
                    row.push_back("");
                }
                ret.push_back(row);
            }
            iter1++;
    }
    
    
    vector<string> newCol;
    for(int k = 0 ; k < left_table->column_names().size(); ++k){
        newCol.push_back(left_table->name() + "." + left_table->column_names()[k]);
    }
    for(int k = 0 ; k < right_table->column_names().size(); ++k){
        newCol.push_back(right_table->name() + "." + right_table->column_names()[k]);
    }
    
    return new Table("LeftJoin", newCol, ret);
  }

  Table* RightJoin(
      const Table* left_table, const string& left_table_key_name,
      const Table* right_table, const string& right_table_key_name) {
    // IMPLEMENT ME
    int id1, id2;
      for(int j = 0 ; j < left_table->column_names().size(); ++j){
            if(left_table_key_name == left_table->column_names()[j]){
                id1 = j;
                break;
            }
        }
        for(int j = 0 ; j < right_table->column_names().size(); ++j){
            if(right_table_key_name == right_table->column_names()[j]){
                id2 = j;
                break;
            }
        }
    vector<vector<string> > ret;
    map<string, vector<vector<string>>> m1, m2;
    
    for(const vector<string>& vs: left_table->data()){
        m1[vs[id1]].push_back(vs);
    }
    for(const vector<string>& vs: right_table->data()){
        m2[vs[id2]].push_back(vs);
    }
    auto iter1 = m1.begin();
    auto iter2 = m2.begin();
    while(iter1 != m1.end() && iter2 != m2.end()){
        if(iter1->first == iter2->first){
            for(const vector<string>& vs1: iter1->second){
                for(const vector<string>& vs2: iter2->second){
                    vector<string> row(vs1.begin(), vs1.end());
                    row.insert(row.end(), vs2.begin(), vs2.end());
                    ret.push_back(row);
                }
            }
            iter1++; iter2++;
        }else if(iter1->first < iter2->first){
            iter1++;
        }else{
            for(const vector<string>& vs2: iter2->second){
                vector<string> row;
                for(int k = 0 ; k < left_table->column_names().size(); ++k){
                    row.push_back("");
                }
                row.insert(row.end(), vs2.begin(), vs2.end());
                ret.push_back(row);
            }
            iter2++;
        }
    }
    
    while(iter2 != m2.end()){
            for(const vector<string>& vs2: iter2->second){
                vector<string> row;
                for(int k = 0 ; k < left_table->column_names().size(); ++k){
                    row.push_back("");
                }
                row.insert(row.end(), vs2.begin(), vs2.end());
                ret.push_back(row);
            }
            iter2++;
    }
    
    vector<string> newCol;
   
    for(int k = 0 ; k < left_table->column_names().size(); ++k){
        newCol.push_back(left_table->name() + "." + left_table->column_names()[k]);
    }
     for(int k = 0 ; k < right_table->column_names().size(); ++k){
        newCol.push_back(right_table->name() + "." + right_table->column_names()[k]);
    }
    return new Table("RightJoin", newCol, ret);
  }

  // Callee will own the returned pointer
  Table* OuterJoin(
      const Table* left_table, const string& left_table_key_name,
      const Table* right_table, const string& right_table_key_name) {
    // IMPLEMENT ME
    int id1, id2;
      for(int j = 0 ; j < left_table->column_names().size(); ++j){
            if(left_table_key_name == left_table->column_names()[j]){
                id1 = j;
                break;
            }
        }
        for(int j = 0 ; j < right_table->column_names().size(); ++j){
            if(right_table_key_name == right_table->column_names()[j]){
                id2 = j;
                break;
            }
        }
    vector<vector<string> > ret;
    map<string, vector<vector<string>>> m1, m2;
    
    for(const vector<string>& vs: left_table->data()){
        m1[vs[id1]].push_back(vs);
    }
    for(const vector<string>& vs: right_table->data()){
        m2[vs[id2]].push_back(vs);
    }
    auto iter1 = m1.begin();
    auto iter2 = m2.begin();
    while(iter1 != m1.end() && iter2 != m2.end()){
        if(iter1->first == iter2->first){
            for(const vector<string>& vs1: iter1->second){
                for(const vector<string>& vs2: iter2->second){
                    vector<string> row(vs1.begin(), vs1.end());
                    row.insert(row.end(), vs2.begin(), vs2.end());
                    ret.push_back(row);
                }
            }
            iter1++; iter2++;
        }else if(iter1->first < iter2->first){
            for(const vector<string>& vs1: iter1->second){
                vector<string> row(vs1.begin(), vs1.end());
                for(int k = 0 ; k < right_table->column_names().size(); ++k){
                    row.push_back("");
                }
                ret.push_back(row);
            }
            iter1++;
        }else{
            for(const vector<string>& vs2: iter2->second){
                vector<string> row;
                for(int k = 0 ; k < left_table->column_names().size(); ++k){
                    row.push_back("");
                }
                row.insert(row.end(), vs2.begin(), vs2.end());
                ret.push_back(row);
            }
            iter2++;
        }
    }
    while(iter1 != m1.end() ){
          for(const vector<string>& vs1: iter1->second){
                vector<string> row(vs1.begin(), vs1.end());
                for(int k = 0 ; k < right_table->column_names().size(); ++k){
                    row.push_back("");
                }
                ret.push_back(row);
            }
            iter1++;
    }
    while(iter2 != m2.end()){
            for(const vector<string>& vs2: iter2->second){
                vector<string> row;
                for(int k = 0 ; k < left_table->column_names().size(); ++k){
                    row.push_back("");
                }
                row.insert(row.end(), vs2.begin(), vs2.end());
                ret.push_back(row);
            }
            iter2++;
    }
    
    vector<string> newCol;
   
    for(int k = 0 ; k < left_table->column_names().size(); ++k){
        newCol.push_back(left_table->name() + "." + left_table->column_names()[k]);
    }
     for(int k = 0 ; k < right_table->column_names().size(); ++k){
        newCol.push_back(right_table->name() + "." + right_table->column_names()[k]);
    }
    return new Table("OuterJoin", newCol, ret);
  }

 private:
  map<string, const Table*> table_map_;
};

#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
  const Table* department_table = new Table(
      "departments",
      { "id", "name" },
      {
        { "0", "engineering" },
        { "1", "finance" }
      });

  const Table* user_table = new Table(
      "users",
      { "id", "department_id", "name" },
      {
        { "0", "0", "Ian" },
        { "1", "0", "John" },
        { "2", "1", "Eddie" },
        { "3", "1", "Mark" },
      });

  const Table* salary_table = new Table(
      "salaries",
      { "id", "user_id", "amount" },
      {
         { "0", "0", "100" },
         { "1", "1", "150" },
         { "2", "1", "200" },
         { "3", "3", "200" },
         { "4", "3", "300" },
         { "5", "4", "400" },
      });

  map<string, const Table*> table_map = map<string, const Table*>();
  table_map["departments"] = department_table;
  table_map["users"] = user_table;
  table_map["salaries"] = salary_table;
  Database* db = new Database(table_map);

  // should print
  // id, department_id, name
  // 1, 0, John
  {
    Table* filtered_table = db->GetTable("users")->Where("id", "1");
    Table* projected_table = filtered_table->Select({ "id", "department_id", "name" });
    projected_table->Print();
    delete projected_table;
    delete filtered_table;
  }

  // should print
  // users.name, departments.name
  // Ian, engineering
  // John, engineering
  {
    Table* table = db->InnerJoin(
        db->GetTable("users"),
        "department_id",
        db->GetTable("departments"),
        "id");

    Table* filtered_table = table->Where("departments.name", "engineering");
    Table* projected_table = filtered_table->Select({ "users.name", "departments.name" });
    projected_table->Print();
    delete projected_table;
    delete filtered_table;
    delete table;
  }

  // should print
  // users.name, salaries.amount
  // Ian, 100
  // John, 150
  // John, 200
  // Mark, 200
  // Mark, 300
  // Eddie,
  {
    Table* table = db->LeftJoin(
        db->GetTable("users"),
        "id",
        db->GetTable("salaries"),
        "user_id");
    Table* projected_table = table->Select({ "users.name", "salaries.amount" });
    projected_table->Print();
    delete projected_table;
    delete table;
  }

  // should print
  // users.name, salaries.amount
  // Ian, 100
  // John, 150
  // John, 200
  // Mark, 200
  // Mark, 300
  // , 400
  {
    Table* table = db->RightJoin(
        db->GetTable("users"),
        "id",
        db->GetTable("salaries"),
        "user_id");
    Table* projected_table = table->Select({ "users.name", "salaries.amount" });
    projected_table->Print();
    delete projected_table;
    delete table;
  }

  // should print
  // users.name, salaries.amount
  // Ian, 100
  // John, 150
  // John, 200
  // Mark, 200
  // Mark, 300
  // Eddie,
  // , 400
  {
    Table* table = db->OuterJoin(
        db->GetTable("users"),
        "id",
        db->GetTable("salaries"),
        "user_id");
    Table* projected_table = table->Select({ "users.name", "salaries.amount" });
    projected_table->Print();
    delete projected_table;
    delete table;
  }

  delete db;

}

#endif

