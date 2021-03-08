void USART_Init (USART_TypeDef * USARTx){
	USARTx->CR1 &= ~USART_CR1_UE;
	USARTx->CR1 &= ~USART_CR1_M;
	USARTx->CR2 &= ~USART_CR2_STOP;
	USARTx->CR1 &= ~USART_CR1_PCE;
	USARTx->CR1 &= ~USART_CR1_OVER8;
	
	USARTx->BRR = 0x208D;
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	USARTx->CR1 |= USART_CR1_UE;
	
	while((USARTx->ISR & USART_ISR_TEACK) == 0);
	
	while((USARTx->ISR & USART_ISR_REACK) == 0);
}
void USART_Read(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t nBytes){
	int i;
	
	for (i = 0; i < nBytes; i++){
		while(!(USARTx->ISR & USART_ISR_RXNE));
		buffer[i] = USARTx->RDR;
	}
}
void USART_Write(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t nBytes){

	int i; 
	
	for (i=0; i < nBytes; i++){
		while(!(USARTx->ISR & USART_ISR_TXE));
		USARTx->TDR = buffer[i] & 0xFF;
	}
	while(!(USARTx->ISR & USART_ISR_TC));
	
	USART1->ICR |= USART_ICR_TCCF;
}