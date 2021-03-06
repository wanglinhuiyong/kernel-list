#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WY");
MODULE_DESCRIPTION("List Module");
MODULE_ALIAS("List module");
//MODULE_INFO(vermagic, VERMAGIC_STRING);

struct student
{
	char name[100];
	int num;
	struct list_head list;
};

//pstudent is a struct array
struct student *pstudent, *tmp_student;
struct list_head student_list;
struct list_head *pos;

int mylist_init(void)
{
	int i = 0;
	INIT_LIST_HEAD(&student_list);
	pstudent = kmalloc(sizeof(struct student)*5, GFP_KERNEL);
	memset(pstudent,0,sizeof(struct student)*5);
	for(i = 0; i < 5; i++)
	{
		sprintf(pstudent[i].name, "student:%d", i+1);
		pstudent[i].num = i+1;
		list_add(&(pstudent[i].list), &student_list);
	}

	list_for_each(pos, &student_list)//pos为struct list_head *类型的指针，student_list为struct list_head类型
	{
		tmp_student = list_entry(pos, struct student, list);//从这能看出来循环遍历的是节点类型为struct student的链表
		printk("<0>student %d name:%s\n", tmp_student->num, tmp_student->name);
	}
	
	return 0;
}

void mylist_exit(void)
{
	int i;
	for(i = 0; i  < 5; i++)
	{
		list_del(&(pstudent[i].list));
	}
	kfree(pstudent);
}

module_init(mylist_init);
module_exit(mylist_exit);
