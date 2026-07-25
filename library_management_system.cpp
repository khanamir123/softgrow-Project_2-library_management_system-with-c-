#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;

struct Book{
	int id;
	string title;
	string author;
	string category;
	int quantity;
	int available_copies = 0;
	int issued_copies = 0;
	bool status;
};

struct Issue{
	int book_id;
	string book_title;
	string student_id;
	string student_name;
	string student_email;
	tm issue_date;
	tm return_date;
};

int next_book_id = 1001;

int total_books = -1;
Book books[200];
int total_issue = 0;
Issue issue_books[200];

class Library{
	public:
		void save_books() {
		    ofstream file("books.txt");
		
		    file << total_books << endl;
			file << next_book_id << endl;
		
		    for(int i = 0; i <= total_books; i++) {
		        file << books[i].id << endl;
		        file << books[i].title << endl;
		        file << books[i].author << endl;
		        file << books[i].category << endl;
		        file << books[i].quantity << endl;
		        file << books[i].available_copies << endl;
		        file << books[i].issued_copies << endl;
		        file << books[i].status << endl;
		    }
		
		    file.close();
		}
		
		
		void save_issues() {
		    ofstream file("issues.txt");
		
		    file << total_issue << endl;
		
		    for(int i = 0; i < total_issue; i++) {
		
		        file << issue_books[i].book_id << endl;
		        file << issue_books[i].book_title << endl;
		        file << issue_books[i].student_id << endl;
		        file << issue_books[i].student_name << endl;
		        file << issue_books[i].student_email << endl;
		
		        file << issue_books[i].issue_date.tm_mday << " "
		             << issue_books[i].issue_date.tm_mon << " "
		             << issue_books[i].issue_date.tm_year << endl;
		
		        file << issue_books[i].return_date.tm_mday << " "
		             << issue_books[i].return_date.tm_mon << " "
		             << issue_books[i].return_date.tm_year << endl;
		    }
		
		    file.close();
		}
		
		void save_data() {
		    save_books();
		    save_issues();
		}
		
		void add_book() {
			Book book; 
			cin.ignore();
			cout << "Enter book title --> ";
			getline(cin, book.title);
			cout << "Enter author name --> ";
			getline(cin, book.author);
			cout << "Enter catogory --> ";
			getline(cin, book.category);
			
			bool existed = false;
			for(int i = 0; i <= total_books; i++) {
				if(books[i].title == book.title && books[i].author == book.author && books[i].category == book.category) {
					cout << "\n\nThis book is already existed!\n";
					cout << "If you want changes in this book choose (Update book) option!" << endl << endl;
					existed = true;
					break;
				}
			}
			
			if(!existed) {
				cout << "Enter quatity --> ";
				cin >> book.quantity;
				while(book.quantity <= 0) {
				    cout << "Quantity must be greater than 0 --> ";
				    cin >> book.quantity;
				}
				cin.ignore();
				
				total_books += 1;
				book.id = next_book_id;
				next_book_id++;
				book.available_copies += book.quantity;
				book.status = true;
				books[total_books] = book;
				
				save_data();
				cout << "\n\n-----Book record-------" << endl;
				cout << left << setw(20) << "Book ID" << book.id << endl;
			    cout << left << setw(20) << "Title" << book.title << endl;
				cout << left << setw(20) << "Author" << book.author << endl;
				cout << left << setw(20) << "Quantity" << book.quantity << endl;
				cout << "\nBook added successfully!" << endl << endl;
			}
			
		}
		
		void display_books() {
			if(total_books < 0) {
				cout << "\n\nNo book in the library!" << endl << endl;
			} else{
				cout << "\n\n---------------------------- Books Record ------------------------------" << endl << endl;
				cout << left << setw(10)  << "ID" << setw(37) << "Title" << setw(37) << "Author" << setw(20) << "Category" << setw(10) << "Status" << "\n\n";
				for(int i = 0; i <= total_books; i++) {
					cout << left << setw(10) << books[i].id;
					cout << left << setw(37) << books[i].title;
					cout << left << setw(37) << books[i].author;
					cout << left << setw(20) << books[i].category;
					if(books[i].status) {
						cout << left << setw(10) << "Available" << endl;
					} else{
						cout << left << setw(10) << "Not Available" << endl;
					}
				}
				 cout << endl << endl;
			}
		}
		
		void update_book() {
			if(total_books < 0) {
				cout << "\n\nNo book in the library!" << endl << endl;
				return;
			}
			bool found = false;
			int book_pos;
			
			while(!found) {
				cout << "\n1: Search book for ammendment!" << endl;
				cout << "0:	Back" << endl << endl;
				
				int option;
				cout << "Enter choice here --> ";
				cin >> option;
				while(option < 0 || option > 1) {
					cout << "Invalid input! Enter again --> ";
					cin >> option;
				}
				
				if(option == 0) {
					break;
				} else {
					int id;
					cout << "Enter book id --> ";
					cin >> id;
					for(int i = 0; i <= total_books; i++) {
						if(id == books[i].id) {
							found = true;
							book_pos = i;
							break;
						}
					}
					
					if(!found) {
						cout << "\nBook not found! Enter correct id" << endl << endl;
					}
				}
			}
			
			if(found) {
				while(true) {
					cout << "\n\n****************************\n";
					cout << "1: Change Title" << endl;
					cout << "2: Change Author" << endl;
					cout << "3: Change Category" << endl;
					cout << "4: Change Quantity" << endl;
					cout << "0: Back" << endl;
					cout << "****************************\n\n";
					
					int choice;
					cout << "Enter choice here --> ";
					cin >> choice;
					while(choice < 0 || choice > 4) {
						cout << "Invalid input! Enter again --> ";
						cin >> choice;
					}
					
					cin.ignore();
					if(choice == 0) {
						break;
					} else if(choice == 1) {
						cout << "Enter new Title here --> ";
						getline(cin, books[book_pos].title);
						save_data();
						cout << "\nTitle changed successfully!" << endl << endl;
					} else if(choice == 2) {
						cout << "Enter new Author here --> ";
						getline(cin, books[book_pos].author);
						save_data();
						cout << "\nAuthor changed successfully!" << endl << endl;
					} else if(choice == 3) {
						cout << "Enter new Category here --> ";
						getline(cin, books[book_pos].category);
						save_data();
						cout << "\nCategory changed successfully!" << endl << endl;
					} else if(choice == 4) {
						int new_quantity;
						cout << "Enter new quantity here --> ";
						cin >> new_quantity;
						
						while(new_quantity < 0) {
							cout << "Quantity can't be negative! Enter again here --> ";
							cin >> new_quantity;
						}
						
						if(new_quantity > books[book_pos].issued_copies) {
							books[book_pos].quantity = new_quantity;
							books[book_pos].available_copies = new_quantity - books[book_pos].issued_copies;
							books[book_pos].status = true;
							save_data();
							cout << "\nQuantity changed successfully!" << endl << endl;
						} else {
							books[book_pos].quantity = books[book_pos].issued_copies;
							books[book_pos].available_copies = 0;
							books[book_pos].status = false;
							save_data();
							cout << "\nQuantity changed successfully!" << endl << endl;
						}
						
					}
				}
			}
			
		}
		
		
		void search_book() {
			if(total_books < 0) {
				cout << "\n\nNo book in the library!" << endl << endl;
				return;
			} else {
				while(true) {
					cout << "\n\n************************************" << endl;
					cout << "1: Search for book" << endl;
					cout << "0: Back" << endl;
					cout << "************************************" << endl << endl;
					
					char choice;
					cout << "Enter choice here --> ";
					cin >> choice;
					while(choice < '0' || choice > '1') {
						cout << "Invalid input! Enter again --> ";
						cin >> choice;
					}
					
					if(choice == '0') {
						break;
					} else {
						bool found = false;
						int book_pos;
						int book_id;
						cout << "Enter book id here --> ";
						cin >> book_id;
						
						for(int i = 0; i <= total_books; i++) {
							if(book_id == books[i].id) {
								book_pos = i;
								found = true;
								break;
							}
						}
						
						if(!found) {
							cout << "\n\nBook not found! Enter correct id." << endl;
						} else {
							cout << "\n\n-----Book Record-----" << endl << endl;
							cout << left <<  setw(40) << "Title" << books[book_pos].title << endl;
							cout << left <<  setw(40) << "Author" << books[book_pos].author << endl;
							cout << left <<  setw(40) << "Category" << books[book_pos].category << endl;
							cout << left <<  setw(40) << "Quantity" << books[book_pos].quantity << endl;
							cout << left <<  setw(40) << "Available Copies" << books[book_pos].available_copies << endl;
							cout << left <<  setw(40) << "Issued Copies" << books[book_pos].issued_copies << endl;
							cout << left <<  setw(40) << "Status";
							if(books[book_pos].status) {
								cout << "Available" << endl;
							} else {
								cout << "Not Available" << endl;
							}
						}
						
					}
				}
				
			}
		}
		
		tm current_date() {
		    time_t t = time(0);
		    tm* now = localtime(&t);
		    return *now;   
		}
		
		tm create_return_date(int d, int m, int y) {
			tm t = {};
			t.tm_mday = d;
			t.tm_mon = m - 1;
			t.tm_year = y - 1900;
			t.tm_isdst = -1;
			return t;
		}
		
		
		void issue_book() {
			if(total_books < 0) {
				cout << "\n\nNo book in the library!" << endl << endl;
				return;
			} else {
				while(true) {
					cout << "\n\n************************************" << endl;
					cout << "1: Search for book" << endl;
					cout << "0: Back" << endl;
					cout << "************************************" << endl << endl;
					
					char choice;
					cout << "Enter choice here --> ";
					cin >> choice;
					while(choice < '0' || choice > '1') {
						cout << "Invalid input! Enter again --> ";
						cin >> choice;
					}
					
					if(choice == '0') {
						break;
					} else {
						bool found = false;
						int book_pos;
						int book_id;
						cout << "Enter book id here --> ";
						cin >> book_id;
						
						for(int i = 0; i <= total_books; i++) {
							if(book_id == books[i].id) {
								book_pos = i;
								found = true;
								break;
							}
						}
						
						if(!found) {
							cout << "\n\nBook not found! Enter correct id." << endl;
						} else if(found && (books[book_pos].available_copies == 0)) {
							cout << "\n\nThid book is not available now!." << endl;
						} else {
							bool already_issued = false;
							cin.ignore();
							string student_id;
							cout << "Enter Student id --> ";
							getline(cin, student_id);
							
							for(int i = 0; i < total_issue; i++) {
								if(issue_books[i].book_id == book_id &&  issue_books[i].student_id == student_id) {
									already_issued = true;
									break;
								}
							}
							
							if(already_issued) {
								cout << "\n\nThis student has already been issued the same book!" << endl << endl;
							} else {
								Issue ib;
								ib.book_id = book_id;
								ib.book_title = books[book_pos].title;
								ib.student_id = student_id;
								cout << "Enter Student name --> ";
								getline(cin, ib.student_name);
								cout << "Enter Student email --> ";
								getline(cin, ib.student_email);
								
								ib.issue_date = current_date();
								
								int day, month, year;
								cout << "Enter the return date (day/month/year)" << endl;
								cout << "Enter day --> ";
								cin >> day;
								while(day < 1 || day > 31) {
									cout << "Invalid input! Enter day --> ";
									cin >> day;
								}
								cout << "Enter month --> ";
								cin >> month;
								while(month < 1 || month > 12) {
									cout << "Invalid input! Enter month --> ";
									cin >> month;
								}
								cout << "Enter year --> ";
								cin >> year;
								while(year < 2025) {
									cout << "Invalid input! Enter year --> ";
									cin >> year;
								}
								ib.return_date = create_return_date(day, month, year);
								
								books[book_pos].issued_copies += 1;
								books[book_pos].available_copies -= 1;
								if(books[book_pos].available_copies == 0) {
								    books[book_pos].status = false;
								}
								
								issue_books[total_issue] = ib;
								total_issue += 1;
								save_data();
								cout << "\n\nBook issued successfully!" << endl << endl;
							}
						}
					}
				} 
			}
		}
		
		
		void return_book() {
			if(total_issue == 0) {
				cout << "\n\nNo book has been issued!" << endl << endl;
				return;
			} else {
				while(true) {
					cout << "\n\n************************************" << endl;
					cout << "1: Search for book" << endl;
					cout << "0: Back" << endl;
					cout << "************************************" << endl << endl;
					
					char choice;
					cout << "Enter choice here --> ";
					cin >> choice;
					while(choice < '0' || choice > '1') {
						cout << "Invalid input! Enter again --> ";
						cin >> choice;
					}
					
					if(choice == '0') {
						break;
					} else {
						bool found = false;
						int book_pos;
						int book_id;
						cout << "Enter book id here --> ";
						cin >> book_id;
						string student_id;
						cout << "Enter student id here --> ";
						cin >> student_id;
						
						for(int i = 0; i < total_issue; i++) {
							if((book_id == issue_books[i].book_id) && (student_id == issue_books[i].student_id)) {
								book_pos = i;
								found = true;
								break;
							}
						}
						
						if(!found) {
							cout << "\n\nThis book has not been issued to this student!" << endl << endl;
						} else {
							tm due = issue_books[book_pos].return_date;
							time_t due_time = mktime(&due);
							time_t current_time = time(0);
							
							double seconds = difftime(current_time, due_time);
							int overdue_days = seconds / (60 * 60 * 24);
							
							
							for(int i = book_pos; i < total_issue - 1; i++) {
								issue_books[i] = issue_books[i+1];
							}
							
							total_issue -= 1;
							for(int i = 0; i <= total_books; i++) {
								if(book_id == books[i].id) {
									books[i].issued_copies -= 1;
									books[i].available_copies += 1;
									books[i].status = true;
									break;
								}
							}
							
							
							if(overdue_days > 0) {
							    int fine_per_day = 50; 
							    int fine = overdue_days * fine_per_day;
							    
							
							    cout << "Overdue Days : " << overdue_days << endl;
							    cout << "Fine : Rs. " << fine << endl;
							}
							else {
							    cout << "No fine!" << endl;
							}
							
							save_data();
							cout << "\n\nBook returned successfully!" << endl << endl;
						}
		        	}
				}     
			}
		}
		
		
		void delete_book() {
			if(total_books < 0) {
				cout << "\n\nNo book in the library!" << endl << endl;
				return;
			} else {
				while(true) {
					cout << "\n\n************************************" << endl;
					cout << "1: Search for book" << endl;
					cout << "0: Back" << endl;
					cout << "************************************" << endl << endl;
					
					char choice;
					cout << "Enter choice here --> ";
					cin >> choice;
					while(choice < '0' || choice > '1') {
						cout << "Invalid input! Enter again --> ";
						cin >> choice;
					}
					
					if(choice == '0') {
						break;
					} else {
						bool found = false;
						int book_pos;
						int book_id;
						cout << "Enter book id here --> ";
						cin >> book_id;
						
						for(int i = 0; i <= total_books; i++) {
							if(book_id == books[i].id) {
								book_pos = i;
								found = true;
								break;
							}
						}
						
						if(!found) {
							cout << "\n\nBook not found! Enter correct id." << endl;
						} else {
							bool issued = false;
							int issue_book_pos;
							for(int i = 0; i < total_issue; i++) {
								if(issue_books[i].book_id == book_id) {
									issued = true;
									issue_book_pos = i;
									break;
								}
							}
							if(!issued) {
								for(int i = book_pos; i < total_books; i++) {
									books[i] = books[i + 1];
								}
								
								total_books -= 1;
								save_data();
								cout << "\n\nBook deleted successfully!" << endl << endl;
							} else {
								char choice;
								cout << endl << endl <<"[" << books[book_pos].issued_copies << "] copies of this book has been issued!" << endl << endl;
								cout << "1: Continue deleting the book with issued data" << endl;
								cout << "0: Return the issued copies" << endl << endl;
								cout << "Enter your choice here --> ";
								cin >> choice;
								
								while(choice != '0' && choice != '1') {
									cout << "Invalid input! Enter again here --> ";
									cin >> choice;
								}
								
								if(choice == '0'){
									break;
								} else {
									for(int i = book_pos; i < total_books; i++) {
										books[i] = books[i + 1];
									}
									
									total_books -= 1;
									
									int save = 0;
									for(int i = 0; i < total_issue; i++) {
										if(issue_books[i].book_id == book_id) {
											continue;
										}
										issue_books[save] = issue_books[i];
										if(issue_books[i].book_id != book_id) {
											save += 1;
										}
									}
									
									total_issue = save;
									
									save_data();
									cout << "\n\nBook deleted successfully!" << endl << endl;
								}
							}
							
						}
					}
				}
			}
		}
		
		
		
		void all_available_books() {
			if(total_books == -1) {
				cout << "\n\nNo book available!" << endl << endl;
				return;
			} else {
				cout << "\n\n---------------------------- Available Books Record ------------------------------" << endl << endl;
				cout << left << setw(10)  << "Book_ID" << setw(35) << "Title" << setw(35) << "Author" << setw(20) << "Category" << setw(16) << "Available copies"<< endl << endl;
				for(int i = 0; i <= total_books; i++) {
					if(books[i].available_copies > 0) {
						cout << left << setw(10) << books[i].id;
						cout << left << setw(35) << books[i].title;
						cout << left << setw(35) << books[i].author;
						cout << left << setw(20) << books[i].category;
						cout << left << setw(20) << books[i].available_copies << endl;
					}
		        }
		       cout << endl << endl;
	        }
		}
		

		void all_issued_books() {
			if(total_issue == 0) {
				cout << "\n\nNo book issued!" << endl << endl;
				return;
			} else {
				cout << "\n\n---------------------------- Issued Books Record ------------------------------" << endl << endl;
				cout << left << setw(10)  << "Book_ID" << setw(35) << "Title" << setw(20) << "Student_ID" << setw(35) << "Student_Name" << endl << endl;
				for(int i = 0; i < total_issue; i++) {
					cout << left << setw(10) << issue_books[i].book_id;
					cout << left << setw(35) << issue_books[i].book_title;
					cout << left << setw(20) << issue_books[i].student_id;
					cout << left << setw(35) << issue_books[i].student_name << endl;
		        }
		       cout << endl << endl;
	        }	
		}
		
		
		void overdue_books() {
			if(total_issue == 0) {
				cout << "\n\nNo book issued!" << endl << endl;
				return;
			} else {
				cout << "\n\n---------------------------- Overdue Books Record ------------------------------" << endl << endl;
				bool found = false;
				for(int i = 0; i < total_issue; i++) {
					tm copy_return = issue_books[i].return_date;
					time_t returning = mktime(&copy_return);
					time_t now = time(0);
					
					double seconds = difftime(now, returning);
					int overdue_days = seconds / (60 * 60 * 24);
					
					int fine_per_day = 50; 
					int fine = overdue_days * fine_per_day;
					
					if(now > returning) {
						found = true;
						tm d = issue_books[i].issue_date;
						cout << left << setw(35) << "Book ID" << issue_books[i].book_id << endl;
						cout << left << setw(35) << "Book Title" << issue_books[i].book_title << endl;
						cout << left << setw(35) << "Student ID" << issue_books[i].student_id << endl;
						cout << left << setw(35) << "Student Name" << issue_books[i].student_name << endl;
						cout << left << setw(35) << "Issue date" << d.tm_mday << "/" << (d.tm_mon + 1) << "/" << (d.tm_year + 1900) << endl;
						cout << left << setw(35) << "Return date" << copy_return.tm_mday << "/" << (copy_return.tm_mon + 1) << "/" << (copy_return.tm_year + 1900)<< endl;
						cout << left << setw(35) << "Overdue Days" << overdue_days << endl;
						cout << left << setw(35) << "Fine" << "Rs. " << fine << endl;
						cout << "-----------------------------------------------------------------------------------------" << endl;
					}
				}
				
				if(!found) {
					cout << "No over due book found!" << endl << endl;
				}
			}  
		}
		
		
		void load_books() {

		    ifstream file("books.txt");
		
		    if(!file) {
		        return;
		    }
		
		    file >> total_books;
		    file >> next_book_id;
		    file.ignore();
		
		    for(int i = 0; i <= total_books; i++) {
		
		        file >> books[i].id;
		        file.ignore();
		
		        getline(file, books[i].title);
		        getline(file, books[i].author);
		        getline(file, books[i].category);
		
		        file >> books[i].quantity;
		        file >> books[i].available_copies;
		        file >> books[i].issued_copies;
		        file >> books[i].status;
		
		        file.ignore();
		    }
		
		    file.close();
		}
		
		
		
		
		
		void load_issues() {
		    ifstream file("issues.txt");
		
		    if(!file) {
		        return;
		    }
		
		    file >> total_issue;
			file.ignore();
		
		    for(int i = 0; i < total_issue; i++) {
		
		        file >> issue_books[i].book_id;
		        file.ignore();
		
		        getline(file, issue_books[i].book_title);
		        getline(file, issue_books[i].student_id);
		        getline(file, issue_books[i].student_name);
		        getline(file, issue_books[i].student_email);
		
		        issue_books[i].issue_date = {};

				file >> issue_books[i].issue_date.tm_mday
				     >> issue_books[i].issue_date.tm_mon
				     >> issue_books[i].issue_date.tm_year;
				
				issue_books[i].issue_date.tm_isdst = -1;
		
		        issue_books[i].return_date = {};

				file >> issue_books[i].return_date.tm_mday
				     >> issue_books[i].return_date.tm_mon
				     >> issue_books[i].return_date.tm_year;
				
				issue_books[i].return_date.tm_isdst = -1;
		
		        file.ignore();
		    }
		
		    file.close();
		}
		
		
		void load_data() {
		    load_books();
		    load_issues();
		}
		
		
		
};

int main() {
	Library lib;
	lib.load_data();
	while(true) {
		cout << "********************************************" << endl;
		cout << " 1: Add book" << endl;
		cout << " 2: Display books" << endl;
		cout << " 3: Update book" << endl;
		cout << " 4: Search book" << endl;
		cout << " 5: Issue book" << endl;
		cout << " 6: Return book" << endl;
		cout << " 7: Delete book" << endl;
		cout << " 8: Available books" << endl;
		cout << " 9: Issued books" << endl;
		cout << "10: Overdue books" << endl;
		cout << " 0: Exit" << endl;
		cout << "*********************************************" << endl << endl;
		
		int choice;
		cout << "Enter your choice --> ";
		cin >> choice;
		while(choice < 0 || choice > 10) {
			cout << "Invalid input! Enter your choice --> ";
			cin >> choice;
		}
		
		if(choice == 0) {
			cout << "\nProgram Ends...";
			break;
		} else if(choice == 1) {
			lib.add_book();
		} else if(choice == 2) {
			lib.display_books();
		} else if(choice == 3) {
			lib.update_book();
		} else if(choice == 4) {
			lib.search_book();
		} else if(choice == 5) {
			lib.issue_book();
		} else if(choice == 6) {
			lib.return_book();
		} else if(choice == 7) {
			lib.delete_book();
		} else if(choice == 8) {
			lib.all_available_books();
		} else if(choice == 9) {
			lib.all_issued_books();
		} else if(choice == 10) {
			lib.overdue_books();
		}
	}
}






