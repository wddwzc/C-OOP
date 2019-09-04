#ifndef GA_H
#define GA_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

// ������Ϣ�ṹ
class Entity {
public:
	std::vector<int> gene;	// ����
	int weight;	// ��������
	int volume;	// �������
	int fitness;	// ������Ӧ��
};

class GAFunc
{
public:
	GAFunc();
	// ��������	�������	��Ⱥ��С	�����������	�������	�������	��������	�������	��ֵ����
	GAFunc(int limitW, int limitV, int popS, int geneN, double probC, double probM, int *WE, int *VO, int *VA);
	~GAFunc();
	// �����Ŵ�����
	void iterateRun(int runNum);
	// �����Ⱥ��Ϣ
	void printPopulation();

private:
	// ���ɳ�ʼ��Ⱥ
	void initPop();
	// Ⱦɫ��ѡ��
	void selectPop();
	// Ⱦɫ�彻��
	void crossPop();
	// Ⱦɫ��ͻ��
	void mutationPop();
	// ������Ⱥ��Ϣ
	void updatePop();
	// ������Ӧ�ȶԸ�����н�������
	void sortPop();

	// �����������������������
	int randNum(int upper, int lower = 0);
	// ���㲢���ø���������
	void setTotalWeight(Entity &entity);
	// ���㲢���ø��������
	void setTotalVolume(Entity &entity);
	// ���㲢���ø�����Ӧ�ȣ��ܼ�ֵ��
	void setFitness(Entity &entity);
	// ��ȡ��Ⱥ����Ӧ��
	int getTotalFit(std::vector<Entity> &pop);

	std::vector<Entity> population;	// ��Ⱥ��Ϣ
	int *weightInfo;	// ��Ʒ������Ϣ
	int *volumeInfo;	// ��Ʒ�����Ϣ
	int *valueInfo;		// ��Ʒ��ֵ��Ϣ
	const int limitWeight;	// ������������
	const int limitVolume;	// �����ݻ�����
	const int popSize;	// ��Ⱥ��С
	const int geneNum;	// Ⱦɫ���ϻ�������
	const double probCross;	// �������
	const double probMutate;	// ͻ�����

};

#endif