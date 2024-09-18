# Virus Collection

## Overview
This repository contains custom-made viruses designed for educational and ethical hacking purposes. **Important**: These viruses are intended to be tested only in controlled and monitored environments.

## Purpose
The purpose of this collection is to explore different types of viruses for ethical hacking by studying their behavior in safe environments.

---

### Self-Replicating Virus

#### Files:
- `corrupt_files.c`
- `corrupt_fileV2.c`

#### Description:
- Uses command-line arguments to test in a controlled setting.
- Operates within a **test folder** to avoid system-wide damage.
- Copies data from all files into a new directory named `doc`.
- Self-replicates by inserting its code into infected files.
- Waits for infected files to be executed before spreading further.
- **Upcoming Feature**: A new version utilizing C's `fork()` function to create additional processes, enhancing the virus’s spread.

---

### Jammer Virus

#### File:
- `jammer.c`

#### Description:
- A simple but effective virus that leverages C's `system()` function to create an infinitely growing process.
- The virus is **safeguarded** by an exit statement that prevents it from running unintentionally.

**Safe Version**:
```c
printf("DO NOT RUN!\nExiting...\n");
exit(0);
```

**Dangerous Version**:
```c
system("dir>>â.ša.exe");
```

### Disclaimer
These viruses are strictly for educational and research purposes. Running these programs in an uncontrolled environment may lead to unintended consequences. **Proceed at your own risk**.

### Future Plans
Adding more virus types and features to further explore ethical hacking methods.
