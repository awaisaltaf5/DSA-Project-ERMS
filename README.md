# 🚨 Emergency Response Management System (ERMS)

The **Emergency Response Management System (ERMS)** is a console-based C++ application designed to efficiently handle, prioritize, and resolve emergency incidents. It supports role-based access for Admins and Staff, dynamically prioritizes emergencies using a priority queue, and maintains a history of resolved cases using a stack. A time-based escalation feature ensures unattended emergencies are re-prioritized for prompt action.

---

## 📌 Features

- 🔐 **Role-Based Access**  
  Supports Admin and Staff users with authentication and different privileges.

- 🚨 **Emergency Reporting**  
  Users can report emergencies with details like type, severity, location, and description.

- ⚡ **Dynamic Priority Queue**  
  Emergencies are automatically sorted based on severity and type using a priority queue.

- ⏱ **Time-Based Escalation**  
  Unresolved emergencies are periodically escalated in priority to ensure timely handling.

- 🧾 **Resolution History (LIFO Stack)**  
  Resolved emergencies are stored and viewable in order of processing.

- 🔎 **Search & Filter**  
  Search resolved cases by keywords and filter active ones by emergency type.

- 📊 **Dashboard Summary**  
  Displays counts of pending emergencies by category.

---

## 🧠 Technical Details

- **Language**: C++  
- **Data Structures**: Singly Linked List, Priority Queue (Linked List), Stack  
- **Platform**: Console (Windows/Linux)  
- **Compiler**: `g++`  
- **IDE**: Code::Blocks, Dev C++, or any terminal-based C++ IDE

---

## 🧪 Testing

- Emergency sorting and escalation verified  
- Login and role-based access tested  
- Stack/queue operations validated  
- Search and filtering confirmed functional

---

## ⚠️ Limitations

- No persistent storage (data is lost after exit)  
- Console-only interface  
- No real-time alerts or GUI

---

## 🚀 Future Enhancements

- File/database integration for permanent storage  
- GUI interface using Qt or similar frameworks  
- Real-time notifications (SMS/email)  
- Geolocation integration and audit logging

---



## 📄 License

This project is open-source and free to use for educational or non-commercial purposes.

---
