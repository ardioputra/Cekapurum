FROM node:14 

WORKDIR ./cekapurum

COPY package*.json ./

RUN npm install

COPY . .

EXPOSE 80

CMD node scripts.js